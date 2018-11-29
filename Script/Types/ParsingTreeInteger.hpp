#ifndef PARSINGTREEINTEGER_HPP
#define PARSINGTREEINTEGER_HPP

#include "ParsingTreeValue.hpp"

struct ParsingTreeFloat;
struct ParsingTreeInteger;
struct ParsingTreeString;
struct ParsingTreeInteger: public ParsingTreeValue
{
    ParsingTreeInteger();

    static ParsingTreeInteger *make(int );
    virtual ParsingTreeValue *execute(MemoryManagement *pMemory);
    virtual ParsingTreeValue* add(ParsingTreeValue* other);
    virtual ParsingTreeValue* remove(ParsingTreeValue* other);
    virtual ParsingTreeValue* divide(ParsingTreeValue* other);
    virtual ParsingTreeValue* multiply(ParsingTreeValue* other);

    int value;
};

#endif // PARSINGTREEINTEGER_HPP
