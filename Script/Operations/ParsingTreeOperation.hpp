#ifndef PARSINGTREEOPERATION_HPP
#define PARSINGTREEOPERATION_HPP

#include "../Types/ParsingTreeValue.hpp"
#include "ParsingTreeOperationType.hpp"
#include "../Memory/MemoryManagement.hpp"
#include "../Types/ParsingTreeInteger.hpp"
#include "../Types/ParsingTreeFloat.hpp"

struct ParsingTreeOperation: public ParsingTreeValue
{
    ParsingTreeOperation();
    ParsingTreeValue *makeOperation(ParsingTreeValue *left, ParsingTreeValue *right);
    virtual ParsingTreeValue *execute(MemoryManagement *pMemory);

    ParsingTreeValue *left;
    ParsingTreeOperationType type;
    ParsingTreeValue *right;
};

#endif // PARSINGTREEOPERATION_HPP
