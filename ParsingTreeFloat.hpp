#ifndef PARSINGTREEFLOAT_HPP
#define PARSINGTREEFLOAT_HPP

#include "ParsingTreeValue.hpp"

struct ParsingTreeString;
struct ParsingTreeInteger;
struct ParsingTreeFloat: public ParsingTreeValue
{
    double value;

    ParsingTreeFloat();

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory);
    static ParsingTreeFloat *makeFloat(double v);
    static ParsingTreeString *makeString(QString str);
    virtual ParsingTreeValue* add(ParsingTreeValue* other);
    virtual ParsingTreeValue* remove(ParsingTreeValue* other);
    virtual ParsingTreeValue* divide(ParsingTreeValue* other);
    virtual ParsingTreeValue* multiply(ParsingTreeValue* other);
};

#endif // PARSINGTREEFLOAT_HPP
