#include "SequenceConditionnal.h"
#include "MemoryManagement.hpp"
#include <QDebug>

SequenceConditionnal::SequenceConditionnal()
{
    childrenOnFailure = nullptr;
    childrenOnSuccess = nullptr;
    next = nullptr;
}

SequenceConditionnal::~SequenceConditionnal()
{

}

bool SequenceConditionnal::canRun() {
    if (conditionnalFunction) {
        bool canRun = true;

        if (childrenOnSuccess)
                canRun = canRun && childrenOnSuccess->canRun();

        if (childrenOnFailure)
               canRun = canRun && childrenOnFailure->canRun();

        if (next) {
            canRun = canRun && next->canRun();
        }

        return true;
    }
    else {
        qDebug() << "Err: Sequence node item is null";
    }
    qDebug() << "Err: Unknown error in sequence node canRun()";

    return false;
}

bool SequenceConditionnal::run(MemoryManagement *apMemory) {
    bool wasSuccesful = false;
    if (conditionnalFunction(apMemory)) {
        if (childrenOnSuccess)
        {
            apMemory->enterScope();
            wasSuccesful = childrenOnSuccess->run(apMemory);
            apMemory->exitScope();
        }
    }
    else {
        if (childrenOnFailure)
        {
           apMemory->enterScope();
           wasSuccesful = childrenOnFailure->run(apMemory);
           apMemory->exitScope();
        }
    }

    bool nextWasSuccessful = false;
    if (next) {
        nextWasSuccessful = next->run(apMemory);
    }

    return wasSuccesful && nextWasSuccessful;
}
