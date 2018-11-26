#ifndef PARSINGTREEINTEGER_HPP
#define PARSINGTREEINTEGER_HPP

#include "ParsingTreeValue.hpp"
#include "ParsingTreeFloat.hpp"

struct ParsingTreeFloat;
struct ParsingTreeInteger;
struct ParsingTreeString;
struct ParsingTreeInteger: public ParsingTreeValue
{
    int value;

    ParsingTreeInteger();

    static ParsingTreeInteger *makeInteger(int );
    static ParsingTreeFloat *makeFloat(double );
    static ParsingTreeString *makeString(QString );
    virtual ParsingTreeValue *execute(MemoryManagement *pMemory);
    virtual ParsingTreeValue* add(ParsingTreeValue* other);
    virtual ParsingTreeValue* remove(ParsingTreeValue* other);
    virtual ParsingTreeValue* divide(ParsingTreeValue* other);
    virtual ParsingTreeValue* multiply(ParsingTreeValue* other);
};

#endif // PARSINGTREEINTEGER_HPP
