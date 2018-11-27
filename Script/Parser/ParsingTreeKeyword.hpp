#ifndef PARSINGTREEKEYWORD_HPP
#define PARSINGTREEKEYWORD_HPP

#include <QtDebug>
#include "ParsingTreeEntryPoint.hpp"
#include "../Types/ParsingTreeValue.hpp"
#include "ParsingTreeKeywordType.hpp"
#include "../Memory/MemoryManagement.hpp"

struct ParsingTreeKeyword: public ParsingTreeEntryPoint
{
    ParsingTreeKeywordType type;
    ParsingTreeValue *value;

    ParsingTreeKeyword()
    {
        debugName = "ParsingTreeKeyword";
    }

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory)
    {
        //qDebug() << "Some Keyword " << type;
        if (type == PTKT_End)
        {
            pMemory->exitScope();
        }
        executeNext(pMemory);
        return nullptr;
    }
};

#endif // PARSINGTREEKEYWORD_HPP
