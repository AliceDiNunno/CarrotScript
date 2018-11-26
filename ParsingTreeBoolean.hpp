#ifndef PARSINGTREEBOOLEAN_HPP
#define PARSINGTREEBOOLEAN_HPP

#include "ParsingTreeValue.hpp"
#include "ParsingTreeInteger.hpp"

struct ParsingTreeBoolean: public ParsingTreeValue
{
    bool value;

    ParsingTreeBoolean();

    static ParsingTreeBoolean *make(bool v);
    virtual ParsingTreeValue *execute(MemoryManagement *pMemory);
    virtual ParsingTreeValue* add(ParsingTreeValue* other);
    virtual ParsingTreeValue* remove(ParsingTreeValue* other);
    virtual ParsingTreeValue* divide(ParsingTreeValue* other);
    virtual ParsingTreeValue* multiply(ParsingTreeValue* other);
};

#endif // PARSINGTREEBOOLEAN_HPP
