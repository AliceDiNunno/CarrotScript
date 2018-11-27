#ifndef PARSINGTREEVALUE_HPP
#define PARSINGTREEVALUE_HPP

#include "../Parser/ParsingTreeExecutable.hpp"

struct ParsingTreeValue: ParsingTreeExecutable
{
    virtual ~ParsingTreeValue(){}

    ParsingTreeValue()
    {
        debugName = "ParsingTreeValue";
    }

    virtual ParsingTreeValue* add(ParsingTreeValue* other)
    {
        Q_UNUSED(other);
        return nullptr; //err;
    }

    virtual ParsingTreeValue* remove(ParsingTreeValue* other)
    {
        Q_UNUSED(other);
        return nullptr; //err;
    }

    virtual ParsingTreeValue* divide(ParsingTreeValue* other)
    {
        Q_UNUSED(other);
        return nullptr; //err;
    }

    virtual ParsingTreeValue* multiply(ParsingTreeValue* other)
    {
        Q_UNUSED(other);
        return nullptr; //err;
    }
};

#endif // PARSINGTREEVALUE_HPP
