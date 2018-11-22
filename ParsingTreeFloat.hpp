#ifndef PARSINGTREEFLOAT_HPP
#define PARSINGTREEFLOAT_HPP

#include "ParsingTreeValue.hpp"

struct ParsingTreeFloat: public ParsingTreeValue
{
    float value;

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory)
    {
        executeNext(pMemory);
        return this;
    }
};

#endif // PARSINGTREEFLOAT_HPP
