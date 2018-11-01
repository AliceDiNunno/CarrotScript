#ifndef SEQUENCELOOP_HPP
#define SEQUENCELOOP_HPP

#include "SequenceConditionnal.h"

class SequenceLoop : public SequenceConditionnal, public QObject
{
public:
    SequenceLoop();
    bool run(MemoryManagement *pMemory) override;
};

#endif // SEQUENCELOOP_HPP
