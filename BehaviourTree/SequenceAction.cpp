//
// Created by Alice Di Nunno on 20/10/2018.
//

#include <QDebug>

#include "SequenceAction.hpp"

SequenceAction::SequenceAction()
{
    childrenOnDone = nullptr;
}

SequenceAction::~SequenceAction()
{

}

bool SequenceAction::canRun() {
    if (functionToRun) {
        if (childrenOnDone != nullptr && !childrenOnDone->canRun())
        {
            qDebug() << "can't run child";
            return false;
        }
        return true;
    }
    else {
        qDebug() << "Err: Sequence node item is null";
    }
    qDebug() << "Err: Unknown error in sequence node canRun()";

    return false;
}

bool SequenceAction::run(MemoryManagement *pMemory) {
    bool wasSuccessful = functionToRun(pMemory);

    if (childrenOnDone) {
        childrenOnDone->run(pMemory);
    }

    return wasSuccessful;
}
