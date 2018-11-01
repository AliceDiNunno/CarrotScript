#include "SequenceLoop.hpp"
#include "MemoryManagement.hpp"
#include <QtDebug>
#include <QThread>

SequenceLoop::SequenceLoop()
{

}

bool SequenceLoop::run(MemoryManagement *apMemory)
{
    bool wasSuccesful = false;
    while (childrenOnSuccess && conditionnalFunction(apMemory)) {
        thread()->wait(1);
        apMemory->enterScope();
        wasSuccesful = childrenOnSuccess->run(apMemory);
        apMemory->exitScope();
    }

    bool nextWasSuccessful = false;
    if (next) {
        nextWasSuccessful = next->run(apMemory);
    }

    return wasSuccesful && nextWasSuccessful;

}
