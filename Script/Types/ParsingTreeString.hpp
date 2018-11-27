#ifndef PARSINGTREESTRING_HPP
#define PARSINGTREESTRING_HPP

#include <QString>
#include "ParsingTreeValue.hpp"

struct ParsingTreeString: public ParsingTreeValue
{
    QString value;

    ParsingTreeString()
    {
        debugName = "ParsingTreeString";
    }

    virtual ParsingTreeValue *execute(MemoryManagement *pMem)
    {
        executeNext(pMem);
        return this;
    }

    static ParsingTreeString *makeString(QString v);

    virtual ParsingTreeValue* add(ParsingTreeValue* other);
};

#endif // PARSINGTREESTRING_HPP
