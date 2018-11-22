#ifndef PARSINGTREEBOOLEAN_HPP
#define PARSINGTREEBOOLEAN_HPP

#include "ParsingTreeValue.hpp"

struct ParsingTreeBoolean: public ParsingTreeValue
{
    bool value;

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory)
    {
        executeNext(pMemory);
        return this;
    }
};

#endif // PARSINGTREEBOOLEAN_HPP
