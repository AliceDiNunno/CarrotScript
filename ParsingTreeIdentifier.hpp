#ifndef PARSINGTREEIDENTIFIER_HPP
#define PARSINGTREEIDENTIFIER_HPP

#include <QByteArray>
#include "ParsingTreeValue.hpp"

struct ParsingTreeIdentifier: public ParsingTreeValue
{
    ParsingTreeValue *name;

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory)
    {
        executeNext(pMemory);
        return this;
    }
};

#endif // PARSINGTREEIDENTIFIER_HPP
