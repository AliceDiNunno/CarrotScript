#ifndef PARSINGTREEARRAY_HPP
#define PARSINGTREEARRAY_HPP

#include <QList>

#include "ParsingTreeValue.hpp"

struct ParsingTreeArray: public ParsingTreeValue
{
    QList<ParsingTreeValue *> values;

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory)
    {
        executeNext(pMemory);
        return this;
    }
};

#endif // PARSINGTREEARRAY_HPP
