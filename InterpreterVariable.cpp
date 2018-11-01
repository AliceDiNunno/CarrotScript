#include <QRegularExpression>
#include "interpreter.h"
#include "BehaviourTree/SequenceAction.hpp"
#include "BehaviourTree/MemoryManagement.hpp"

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
