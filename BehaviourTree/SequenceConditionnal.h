#ifndef SEQUENCECONDITIONNAL_H
#define SEQUENCECONDITIONNAL_H

#include "SequenceAction.hpp"

class SequenceConditionnal: public SequenceNode
{
public:
    virtual ~SequenceConditionnal();
    SequenceConditionnal();

public:
    SequenceFunction conditionnalFunction; //Function that will return true if it should be executed

    SequenceNode *childrenOnSuccess;
    SequenceNode *childrenOnFailure;

    SequenceNode *next;

    bool canRun();
    virtual bool run(MemoryManagement *apMemory);

};

#endif // SEQUENCECONDITIONNAL_H
