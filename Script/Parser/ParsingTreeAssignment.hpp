#ifndef PARSINGTREEASSIGNEMNT_HPP
#define PARSINGTREEASSIGNEMNT_HPP

#include <QByteArray>
#include "ParsingTreeEntryPoint.hpp"

//Todo: move to memory ?
struct ParsingTreeValue;
struct ParsingTreeAccessor;
class MemoryManagement;
struct ParsingTreeAssignment: public ParsingTreeEntryPoint
{
    ParsingTreeAssignment();

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory);

    QByteArray symbol;
    ParsingTreeValue *from;
    ParsingTreeAccessor *to;
};

#endif // PARSINGTREEASSIGNMENT_HPP
