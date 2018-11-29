#ifndef PARSINGTREECONDITION_HPP
#define PARSINGTREECONDITION_HPP

#include "ParsingTreeKeyword.hpp"
#include "../Types/ParsingTreeBoolean.hpp"

//Todo: move to operations ?
struct ParsingTreeComparison;
struct ParsingTreeCondition: public ParsingTreeKeyword
{
    ParsingTreeCondition();

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory);

    ParsingTreeComparison *condition = nullptr;
};

#endif // PARSINGTREECONDITION_HPP
