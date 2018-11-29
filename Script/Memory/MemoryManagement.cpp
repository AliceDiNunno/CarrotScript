#include "MemoryManagement.hpp"

#include "../Exceptions/BadAccessorException.hpp"
#include "../Exceptions/UnknownVariableException.hpp"
#include "../Types/ParsingTreeBoolean.hpp"
#include "../Types/ParsingTreeString.hpp"
#include "../Types/ParsingTreeInteger.hpp"
#include "../Types/ParsingTreeArray.hpp"
#include "../Types/ParsingTreeFloat.hpp"
#include "../Operations/ParsingTreeOperation.hpp"
#include "ParsingTreeVariabeRead.hpp"

MemoryManagement::MemoryManagement()
{
    reset();
}

MemoryManagement::~MemoryManagement()
{

}

void MemoryManagement::reset()
{
    scopes = QList<QList<ScriptVariable *> *>();
    bindings = QMap<QByteArray, ScriptClassBinding *>();
    scopes.append(new QList<ScriptVariable *>());
}

ParsingTreeValue *MemoryManagement::readChild(ParsingTreeAccessor *accs, ParsingTreeValue *pValue)
{
    if (accs == nullptr || pValue == nullptr || accs->child == nullptr)
    {
        return nullptr;
    }

    if (ParsingTreeArray *pta = dynamic_cast<ParsingTreeArray *>(pValue))
    {
        ParsingTreeAccessor *pChild = accs->child;
        if (ParsingTreeInteger *pti = dynamic_cast<ParsingTreeInteger *>(pChild->name))
        {
            return (pta->values.at(pti->value));
        }
        throw BadAccessorException(pChild->debugName + " child accessor is unsupported", "", accs->line, accs->lineNumber, -1);
    }
    else
    {
        throw BadAccessorException(pValue->debugName + " accessor is unsupported", "", accs->line, accs->lineNumber, -1);
    }
}

ParsingTreeValue *MemoryManagement::readValue(ParsingTreeAccessor *name)
{
    if (name == nullptr)
        return nullptr;
    QString varName = translateValue(name).toString();
    ParsingTreeValue *vp = nullptr;
    for (int iScope = 0; iScope < scopes.count(); iScope++)
    {
        QList<ScriptVariable *> *vars = scopes.at(iScope);
        for (int iVar = 0; iVar < vars->count(); iVar++)
        {
            ScriptVariable *var = vars->at(iVar);
            if (varName == var->first)
            {
                QString str = "FETCH %1 = %2";
                str = str.arg(QString(var->first)).arg(translateValue(var->second).toString());
                emit info(str);

                vp = var->second;
                break;
            }
        }
        if (vp != nullptr)
            break;
    }
    if (vp == nullptr)
    {
        throw UnknownVariableException(varName + " is undefined", "", name->line, name->lineNumber, -1);
    }
    if (name->child == nullptr)
        return vp;
    return readChild(name, vp);
}

// TODO: Check For Functions
ParsingTreeValue *MemoryManagement::callFunction(ParsingTreeIdentifier *ids, QList<ParsingTreeValue *> args)
{
    if (translateValue(ids->name) == "message")
    {
        QList<QVariant > ptvlist = QList<QVariant >();
        for (int iArg = 0; iArg < args.count(); iArg++)
        {
            ParsingTreeValue *pCurrentValue = args.at(iArg);
            if (ParsingTreeVariabeRead *ptvr = dynamic_cast<ParsingTreeVariabeRead *>(pCurrentValue))
            {
                ptvlist << translateValue(readValue(ptvr->id));
            }
            else
            {
                if (ParsingTreeOperation *pto = dynamic_cast<ParsingTreeOperation *>(pCurrentValue))
                {
                    ParsingTreeValue *ptv = pto->execute(this);
                    ptvlist << translateValue(ptv);
                }
                else if(ParsingTreeAccessor *pta = dynamic_cast<ParsingTreeAccessor *>(pCurrentValue))
                {
                    ParsingTreeValue *ptv = readValue(pta);
                    ptvlist << translateValue(ptv);
                }
                else
                {
                    ptvlist << translateValue(pCurrentValue);
                }
            }
        }

        if (ptvlist.count() >= 1)
        {
            emit message(ptvlist.at(0).toString());
        }
    }

    return nullptr;
}

void MemoryManagement::setValue(ParsingTreeAccessor *accs, ParsingTreeValue *val)
{
    if (!val || !accs)
    {
        //err
        return;
    }

    ScriptVariable sv;
    sv.second = val->execute(this);

    if (accs->child == nullptr)
    {
        ParsingTreeValue *pName = accs->execute(this);
        sv.first = translateValue(pName).toByteArray();
    }
    insert(sv);
}

QVariant MemoryManagement::translateValue(ParsingTreeValue *val)
{
    if (ParsingTreeBoolean *pValue = dynamic_cast<ParsingTreeBoolean *>(val))
    {
        return pValue->value;
    }
    else if (ParsingTreeString *pValue = dynamic_cast<ParsingTreeString *>(val))
    {
        return pValue->value;
    }
    else if (ParsingTreeInteger *pValue = dynamic_cast<ParsingTreeInteger *>(val))
    {
        return pValue->value;
    }
    else if (ParsingTreeFloat *pValue = dynamic_cast<ParsingTreeFloat *>(val))
    {
        return pValue->value;
    }
    else if (ParsingTreeIdentifier *pValue = dynamic_cast<ParsingTreeIdentifier *>(val))
    {
        return translateValue(pValue->name);
    }
    else if (ParsingTreeAccessor *pValue = dynamic_cast<ParsingTreeAccessor *>(val))
    {
        return translateValue(pValue->name); //Todo: return all accesspr data
    }
    else if (ParsingTreeArray *pValue = dynamic_cast<ParsingTreeArray *>(val))
    {
        QList<QVariant> varl;
        for (int iP = 0; iP < pValue->values.count(); iP++)
        {
            varl.append(translateValue(pValue->values.at(iP)));
        }
        return QVariant(varl);
    }
    else
    {
        return QVariant();
        //err
    }
}

void MemoryManagement::insert(ScriptVariable sv)
{
    for (int iScope = 0; iScope < scopes.count(); iScope++)
    {
        QList<ScriptVariable *> *vars = scopes.at(iScope);
        for (int iVar = 0; iVar < vars->count(); iVar++)
        {
            ScriptVariable *var = vars->at(iVar);
            if (sv.first == var->first)
            {
                var->second = sv.second;
                QString str = "Update %1 = %2";
                str = str.arg(QString(sv.first)).arg(translateValue(var->second).toString());
                emit info(str);
                return;
            }
        }
    }
    ScriptVariable *siv = new ScriptVariable();
    siv->first = sv.first;
    siv->second = sv.second;
    scopes.last()->append(siv);
    QString str = "Set %1 = %2";
    str = str.arg(QString(siv->first)).arg(translateValue(siv->second).toString());
    emit info(str);
}

void MemoryManagement::enterScope()
{
    qDebug() << "enter scope";
    scopes.append(new QList<ScriptVariable *>());
}

void MemoryManagement::exitScope()
{
    if (scopes.count() <= 1)
        qDebug() << ("CANNOT EXIT SCOPE"); //ERR
    else
        scopes.removeLast();
}
