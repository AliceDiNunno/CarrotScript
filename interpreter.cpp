#include <QFile>
#include <QDebug>

#include <QRegularExpression>

#include "interpreter.h"
#include "BehaviourTree/SequenceAction.hpp"
#include "BehaviourTree/SequenceConditionnal.h"
#include "BehaviourTree/SequenceLoop.hpp"
#include "BehaviourTree/MemoryManagement.hpp"

extern "C" {
    bool isEqual(QVariant a, QVariant b) {
        return a.operator==(b);
    }
    bool isDifferent(QVariant a, QVariant b) {
        return !isEqual(a, b);
    }
    bool isLesserThan(QVariant a, QVariant b) {
        return a.operator<(b);
    }
    bool isGreaterThan(QVariant a, QVariant b) {
        return a.operator>(b);
    }
    bool isGreaterOrEqual(QVariant a, QVariant b) {
        return !isLesserThan(a, b);
    }
    bool isLesserOrEqual(QVariant a, QVariant b) {
        return !isGreaterThan(a, b);
    }
};

Interpreter::Interpreter()
{
    _pSequence = new Sequence();
    _scriptPosition = -1;
    _pSequence->triggerId = "empty";
    _opcodes = {
        { "set", &Interpreter::opcSet },
        { "add", &Interpreter::opcAdd },
        { "message", &Interpreter::opcMessage },

        //Conditionnal
        { "if", &Interpreter::opcIf },
        { "while", &Interpreter::opcWhile },
        { "else", &Interpreter::opcElse },
        { "end", &Interpreter::opcEnd },
    };
    _comparisonMethods = {
        { "==", &isEqual },
        { "!=", &isDifferent },
        { ">", &isGreaterThan },
        { "<", &isLesserThan },
        { ">=", &isGreaterOrEqual },
        { "<=", &isLesserOrEqual }
    };
}

Interpreter::~Interpreter()
{

}

void Interpreter::loadFile(QString aFile)
{
    QFile *f = new QFile(aFile);
    if (f->open(QIODevice::ReadOnly))
    {
        emit info("Loaded file: " + aFile);
        QByteArray data = f->readAll();
        parseAll(data);
    }
    else
        emit error("Unable to open file: " + aFile);
}

void Interpreter::run()
{
    emit info("Running...");

    _pSequence->run();
}

void Interpreter::parseAll(QString str)
{
    _instructions = str.split("\n");
    _instructions.removeAll("");

    emit alert("Parsing: ");
    _pSequence->start = parseNext();
}

SequenceNode *Interpreter::parseNext()
{
    _scriptPosition++;
    if (_scriptPosition >= _instructions.count())
        return nullptr;
    QString currentInstruction = _instructions.at(_scriptPosition);
    currentInstruction.replace("\t", "");
    currentInstruction.replace("\r", "");
    emit alert(currentInstruction);

    QStringList command = currentInstruction.split(" ");
    qDebug() << currentInstruction;
    command.removeAll("");

    QString cmd_opcode = command.at(0);
    _lastInstruction = cmd_opcode;

    for (int iOpcodeIndex = 0; iOpcodeIndex < _opcodes.count(); iOpcodeIndex++)
    {
        OpcodeSet code = _opcodes.at(iOpcodeIndex);
        if (cmd_opcode == code.opcode)
        {
            command.removeFirst();

            if (code.run != nullptr)
            {
                return (this->*(code.run))(command);
            }
            return nullptr;
        }
    }
    emit error ("Unknown opcode: " + cmd_opcode);
    return nullptr;
}

QVariant Interpreter::getValue(QString str, MemoryManagement *pMemory)
{
    QRegularExpression reB("^([0-9]*)$"); //check if pure number
    QRegularExpressionMatch matchB = reB.match(str);
    if (matchB.hasMatch())
    {
        return matchB.captured(0).toInt();
    }

    QRegularExpression reA("^\"(.*?)\"$"); //check if pure string
    QRegularExpressionMatch match = reA.match(str);

    if (match.hasMatch())
    {
        return match.captured(1);
    }

    if (str == "true" || str == "false")
    {
        return QVariant(str).toBool();
    }


    return pMemory->get(str);
}

bool Interpreter::compare(QVariant a, QVariant b, QString comparisonOperator)
{
    for (int iComparisonMethod = 0; iComparisonMethod < _comparisonMethods.count(); iComparisonMethod++)
    {
        ComparisonMethod cm = _comparisonMethods.at(iComparisonMethod);
        if (cm.ComparisonOperator == comparisonOperator)
        {
            return cm.compare(a, b);
        }
    }
    return false;
}

SequenceNode *Interpreter::opcSet(QStringList aLine)
{
    //TODO: Can copy variable

    SequenceAction *setNode = new SequenceAction();
    setNode->arguments = aLine;

    SequenceFunction pauseMusicFunction = [this, aLine](MemoryManagement *pMemory) {
        if (aLine.count() < 2) {
            return false;
        }
        QString key = aLine.value(0);
        QVariant v = QVariant::fromValue(aLine.value(1));

        QRegularExpression reA("^\"(.*?)\"$"); //check if pure string
        QRegularExpression reB("^([0-9].*)$"); //starts with number
        QRegularExpression reC("^[a-zA-Z0-9_]*$"); //alphanumerical
        QRegularExpression reD("^[0-9]+$"); //onlyNumber
        QRegularExpressionMatch match = reA.match(v.toString());
        QRegularExpressionMatch match1 = reA.match(key);
        QRegularExpressionMatch match2 = reB.match(key);
        QRegularExpressionMatch match3 = reC.match(key);

        QRegularExpressionMatch match4 = reD.match(v.toString());
        QRegularExpressionMatch match5 = reC.match(v.toString());
        QRegularExpressionMatch match7 = reB.match(v.toString());

        if (match1.hasMatch())
        {
            emit error("Variable name can't be a string");
        }

        if (key == "true" || key == "false")
        {
            emit error("Variable name can't be 'true' or 'false'");
        }

        if (match2.hasMatch())
        {
            emit error("Variable name can't start with a number");
        }

        if (!match3.hasMatch())
        {
            emit error("Variable name can only contains '_' and alphanumerical characters");
        }

        if (match.hasMatch())
        {
            v = match.captured(1);
        }
        else if (!match4.hasMatch() && match5.hasMatch() && !match7.hasMatch())
        {
            v = pMemory->get(v.toString());
        }

        pMemory->set(key, v);
        return true;
    };

    setNode->functionToRun = pauseMusicFunction;
    setNode->childrenOnDone = parseNext();

    return setNode;
}

SequenceNode *Interpreter::opcMessage(QStringList aLine)
{
    SequenceAction *setNode = new SequenceAction();
    setNode->arguments = aLine;

    SequenceFunction pauseMusicFunction = [this, aLine](MemoryManagement *pMemory) {
        QString msg = aLine.join(" ");

        QRegularExpression reA("\\{(.*?)\\}");
        QString input(aLine.join(" "));
        QRegularExpressionMatch match = reA.match(input);

        QRegularExpressionMatchIterator i = reA.globalMatch(input);
        while (i.hasNext()) {
            QRegularExpressionMatch match = i.next();
            if (match.hasMatch()) {
                msg.replace(match.captured(0), pMemory->get(match.captured(1)).toString());
            }
        }

        emit info(msg);

        return true;
    };

    setNode->functionToRun = pauseMusicFunction;
    setNode->childrenOnDone = parseNext();

    return setNode;
}

SequenceNode *Interpreter::opcIf(QStringList aLine)
{
    SequenceConditionnal *ifNode = new SequenceConditionnal();
    ifNode->arguments = aLine;

    SequenceFunction pauseMusicFunction = [this, aLine](MemoryManagement *pMemory) {
        qDebug() << aLine;
        if (aLine.count() == 1)
        {
            QVariant v = getValue(aLine.at(0), pMemory);
            return v.toBool();
        }
        return compare(getValue(aLine.at(0), pMemory), getValue(aLine.at(2), pMemory), aLine.at(1));
    };

    ifNode->conditionnalFunction = pauseMusicFunction;

    _conditionnals.push(ifNode);

    ifNode->childrenOnSuccess = parseNext();

    return ifNode;
}

SequenceNode *Interpreter::opcAdd(QStringList aLine)
{
    SequenceAction *setNode = new SequenceAction();
    setNode->arguments = aLine;

    SequenceFunction pauseMusicFunction = [this, aLine](MemoryManagement *pMemory) {
        if (aLine.count() < 2) {
            emit error(QString("Not enough arguments for 'Set' expected: 2, got %1").arg(aLine.count()));
            return false;
        }

        QString key = aLine.at(0);
        int value = pMemory->get(key).toInt() + aLine.at(1).toInt();
        pMemory->set(key, value);

        return true;
    };

    setNode->functionToRun = pauseMusicFunction;
    setNode->childrenOnDone = parseNext();

    return setNode;
}

SequenceNode *Interpreter::opcWhile(QStringList aLine)
{
    SequenceLoop *ifNode = new SequenceLoop();
    ifNode->arguments = aLine;

    SequenceFunction pauseMusicFunction = [this, aLine](MemoryManagement *pMemory) {
        if (aLine.count() == 1)
        {
            QVariant v = getValue(aLine.at(0), pMemory);
            return v.toBool();
        }
        return compare(getValue(aLine.at(0), pMemory), getValue(aLine.at(2), pMemory), aLine.at(1));
    };

    ifNode->conditionnalFunction = pauseMusicFunction;

    _conditionnals.push(ifNode);

    ifNode->childrenOnSuccess = parseNext();

    return ifNode;
}

SequenceNode *Interpreter::opcElse(QStringList aLine)
{
    if (_conditionnals.count() <= 0)
    {
        emit error("Can't use else without previous if");
        return nullptr;
    }
    SequenceConditionnal *sc = _conditionnals.top();
    if (dynamic_cast<SequenceLoop *>(sc))
    {
        emit error("Can't use else whitout previous if");
        return nullptr;
    }
    sc->arguments = aLine;

    sc->childrenOnFailure = parseNext();
    return nullptr;
}


SequenceNode *Interpreter::opcEnd(QStringList aLine)
{
    if (_conditionnals.count() <= 0)
    {
        emit error("Can't use end without previous if/else");
        return nullptr;
    }
    SequenceConditionnal *sc = _conditionnals.pop();
    sc->arguments = aLine;

    sc->next = parseNext();
    return nullptr;
}
