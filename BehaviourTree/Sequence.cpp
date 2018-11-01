//
// Created by Alice Di Nunno on 20/10/2018.
//

#include "Sequence.hpp"
#include "SequenceAction.hpp"
#include "MemoryManagement.hpp"

bool Sequence::isValid() {
    if (triggerId == "") {
        qDebug() << "Err: Trigger is empty";
        return false;
    }
    if (start == nullptr) {
        qDebug() << "Err: Start sequence node is invalid";
        return false;
    }
    qDebug() << "Sequence root is ok";
    return start->canRun();
}

bool Sequence::run() {
    if (!isValid()) {
        qDebug() << "Can't run invalid sequence";
        return false;
    }

    qDebug() << "Running sequence";
    //TODO: init variables
    start->run(new MemoryManagement());
    return true;
}
