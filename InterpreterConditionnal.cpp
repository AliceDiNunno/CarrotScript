#include "interpreter.h"
#include "BehaviourTree/SequenceLoop.hpp"

SequenceNode *Interpreter::opcIf(QStringList aLine)
{
    SequenceConditionnal *ifNode = new SequenceConditionnal();
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
