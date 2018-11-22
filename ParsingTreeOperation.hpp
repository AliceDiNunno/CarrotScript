#ifndef PARSINGTREEOPERATION_HPP
#define PARSINGTREEOPERATION_HPP

#include "ParsingTreeValue.hpp"
#include "ParsingTreeOperationType.hpp"

struct ParsingTreeOperation: public ParsingTreeValue
{
    ParsingTreeValue *left;
    ParsingTreeOperationType type;
    ParsingTreeValue *right;

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory)
    {
        executeNext(pMemory);
        return nullptr;
    }
};

#endif // PARSINGTREEOPERATION_HPP
