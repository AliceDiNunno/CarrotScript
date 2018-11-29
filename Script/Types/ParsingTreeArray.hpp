#ifndef PARSINGTREEARRAY_HPP
#define PARSINGTREEARRAY_HPP

#include <QList>

#include "ParsingTreeValue.hpp"

struct ParsingTreeArray: public ParsingTreeValue
{
    ParsingTreeArray();

    virtual ParsingTreeValue *execute(MemoryManagement *);

    QList<ParsingTreeValue *> values;
};

#endif // PARSINGTREEARRAY_HPP
