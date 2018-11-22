#ifndef PARSINGTREEINTEGER_HPP
#define PARSINGTREEINTEGER_HPP

#include "ParsingTreeValue.hpp"

struct ParsingTreeInteger: public ParsingTreeValue
{
    int value;

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory)
    {
        executeNext(pMemory);
        return this;
    }
};

#endif // PARSINGTREEINTEGER_HPP
