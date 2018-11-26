#ifndef PARSINGTREEARRAY_HPP
#define PARSINGTREEARRAY_HPP

#include <QList>

#include "ParsingTreeValue.hpp"

struct ParsingTreeArray: public ParsingTreeValue
{
    QList<ParsingTreeValue *> values;

    ParsingTreeArray()
    {
        debugName = "ParsingTreeArray";
    }

    virtual ParsingTreeValue *execute(MemoryManagement *)
    {
        return nullptr;
    }
};

#endif // PARSINGTREEARRAY_HPP
