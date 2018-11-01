//
// Created by Alice Di Nunno on 20/10/2018.
//

#ifndef CARROTCLOUDAPI_SEQUENCENODE_HPP
#define CARROTCLOUDAPI_SEQUENCENODE_HPP

#include <QVariant>
#include <QUuid>

#include "SequenceNode.h"

class SequenceAction: public SequenceNode {
public:
    virtual ~SequenceAction();
    SequenceAction();

public:
    SequenceFunction functionToRun;

    SequenceNode *childrenOnDone;

    bool canRun();
    bool run(MemoryManagement *pMemory);
};


#endif //CARROTCLOUDAPI_SEQUENCENODE_HPP
