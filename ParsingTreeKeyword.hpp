#ifndef PARSINGTREEKEYWORD_HPP
#define PARSINGTREEKEYWORD_HPP

#include <QtDebug>
#include "ParsingTreeEntryPoint.hpp"
#include "ParsingTreeValue.hpp"
#include "ParsingTreeKeywordType.hpp"

struct ParsingTreeKeyword: public ParsingTreeEntryPoint
{
    ParsingTreeKeywordType type;
    ParsingTreeValue *value;

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory)
    {
        qDebug() << "Some Keyword " << type;
        executeNext(pMemory);
        return nullptr;
    }
};

#endif // PARSINGTREEKEYWORD_HPP
