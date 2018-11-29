#ifndef PARSINGTREEBOOLEAN_HPP
#define PARSINGTREEBOOLEAN_HPP

#include "ParsingTreeValue.hpp"

struct ParsingTreeBoolean: public ParsingTreeValue
{
    ParsingTreeBoolean();

    static ParsingTreeBoolean *make(bool v);
    virtual ParsingTreeValue *execute(MemoryManagement *pMemory);
    virtual ParsingTreeValue* add(ParsingTreeValue* other);
    virtual ParsingTreeValue* remove(ParsingTreeValue* other);
    bool value;
};

#endif // PARSINGTREEBOOLEAN_HPP
