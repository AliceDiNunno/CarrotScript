#ifndef PARSINGTREESTRING_HPP
#define PARSINGTREESTRING_HPP

#include <QString>
#include "ParsingTreeValue.hpp"

struct ParsingTreeString: public ParsingTreeValue
{
    ParsingTreeString();

    static ParsingTreeString *make(QString v);
    virtual ParsingTreeValue *execute(MemoryManagement *pMem);
    virtual ParsingTreeValue* add(ParsingTreeValue* other);

    QString value;
};

#endif // PARSINGTREESTRING_HPP
