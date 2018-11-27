#ifndef PARSINGTREEIDENTIFIER_HPP
#define PARSINGTREEIDENTIFIER_HPP

#include <QByteArray>
#include "../Types/ParsingTreeValue.hpp"

struct ParsingTreeIdentifier: public ParsingTreeValue
{
    ParsingTreeValue *name;

    ParsingTreeIdentifier()
    {
        debugName = "ParsingTreeIdentifier";
    }

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory)
    {
        executeNext(pMemory);
        return this;
    }
};

#endif // PARSINGTREEIDENTIFIER_HPP
