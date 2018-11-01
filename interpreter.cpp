#include <QFile>
#include <QDebug>

#include <QRegularExpression>

#include "interpreter.h"
#include "BehaviourTree/SequenceAction.hpp"
#include "BehaviourTree/SequenceConditionnal.h"
#include "BehaviourTree/SequenceLoop.hpp"
#include "BehaviourTree/MemoryManagement.hpp"

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

void Interpreter::run()
{
    emit info("Running...");

    _pSequence->run();
}

void Interpreter::parseAll(QString str)
{
    _instructions = str.split("\n");

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

    if (currentInstruction == "")
        return parseNext();

    emit alert(currentInstruction);

    QStringList command = currentInstruction.split(" ");
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
                SequenceNode *pNode = (this->*(code.run))(command);

                if (pNode)
                {
                    pNode->line = currentInstruction;
                    pNode->lineNumber = _scriptPosition;
                }
                return pNode;
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
