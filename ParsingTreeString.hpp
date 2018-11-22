#ifndef PARSINGTREESTRING_HPP
#define PARSINGTREESTRING_HPP

#include <QString>
#include "ParsingTreeValue.hpp"

struct ParsingTreeString: public ParsingTreeValue
{
    QString value;

    virtual ParsingTreeValue *execute(MemoryManagement *pMem)
    {
        executeNext(pMem);
        return this;
    }
};

#endif // PARSINGTREESTRING_HPP
