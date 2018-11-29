#ifndef PARSINGTREEIDENTIFIER_HPP
#define PARSINGTREEIDENTIFIER_HPP

#include <QByteArray>
#include "../Types/ParsingTreeValue.hpp"

class MemoryManagement;
struct ParsingTreeIdentifier: public ParsingTreeValue
{
    ParsingTreeIdentifier();

    ParsingTreeValue *name;
    virtual ParsingTreeValue *execute(MemoryManagement *pMemory);
};

#endif // PARSINGTREEIDENTIFIER_HPP
