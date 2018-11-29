#ifndef PARSINGTREEFLOAT_HPP
#define PARSINGTREEFLOAT_HPP

#include "ParsingTreeValue.hpp"

struct ParsingTreeString;
struct ParsingTreeInteger;
struct ParsingTreeFloat: public ParsingTreeValue
{
    ParsingTreeFloat();

    static ParsingTreeFloat *make(double v);
    virtual ParsingTreeValue *execute(MemoryManagement *pMemory);
    virtual ParsingTreeValue* add(ParsingTreeValue* other);
    virtual ParsingTreeValue* remove(ParsingTreeValue* other);
    virtual ParsingTreeValue* divide(ParsingTreeValue* other);
    virtual ParsingTreeValue* multiply(ParsingTreeValue* other);

    double value;
};

#endif // PARSINGTREEFLOAT_HPP
