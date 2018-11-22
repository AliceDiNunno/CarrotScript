#include "MemoryManagement.hpp"

#include "ParsingTreeBoolean.hpp"
#include "ParsingTreeString.hpp"
#include "ParsingTreeInteger.hpp"
#include "ParsingTreeArray.hpp"
#include "ParsingTreeFloat.hpp"

MemoryManagement::MemoryManagement()
{

}

MemoryManagement::~MemoryManagement()
{

}

ParsingTreeValue *MemoryManagement::readValue(ParsingTreeAccessor *name)
{
    QString varName = translateValue(name).toString();
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

                return var->second;
            }
        }
    }
    emit info(QString("Fetch unknown (%1)").arg(varName));
    return nullptr;
}

ParsingTreeValue *MemoryManagement::callFunction(ParsingTreeIdentifier *ids, QList<ParsingTreeValue *> args)
{
    ParsingTreeAccessor *accs = dynamic_cast<ParsingTreeAccessor *>(ids);
    if (translateValue(accs->name) == "message")
    {
        QList<QVariant > ptvlist = QList<QVariant >();
        for (int iArg = 0; iArg < args.count(); iArg++)
        {
            if (ParsingTreeIdentifier *pti = dynamic_cast<ParsingTreeIdentifier *>(args.at(iArg)))
            {
                ptvlist << translateValue(pti->execute(this));
            }
            else
            {
                ptvlist << translateValue(args.at(iArg));
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
        sv.first = translateValue(accs->execute(this)).toByteArray();
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
        //TODO
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
        qDebug() << "ERR TRANSLATE";
        //err
    }

    return QVariant();
}

void MemoryManagement::insert(ScriptVariable sv)
{
    if (scopes.isEmpty())
        scopes.append(new QList<ScriptVariable *>());
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
    scopes.append(new QList<ScriptVariable *>());
    emit info(QString("Enter scope: %1").arg(scopes.count()));
}

void MemoryManagement::exitScope()
{
    emit info(QString("Exit scope: %1").arg(scopes.count()));
    scopes.removeLast();
}
