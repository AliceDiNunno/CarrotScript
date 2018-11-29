#ifndef PARSINGTREEVALUE_HPP
#define PARSINGTREEVALUE_HPP

#include "../Parser/ParsingTreeExecutable.hpp"

struct ParsingTreeValue: ParsingTreeExecutable
{
    ParsingTreeValue();
    virtual ~ParsingTreeValue();

    virtual ParsingTreeValue* add(ParsingTreeValue* other);
    virtual ParsingTreeValue* remove(ParsingTreeValue* other);
    virtual ParsingTreeValue* divide(ParsingTreeValue* other);
    virtual ParsingTreeValue* multiply(ParsingTreeValue* other);
};

#endif // PARSINGTREEVALUE_HPP
