#ifndef PARSINGTREEKEYWORD_HPP
#define PARSINGTREEKEYWORD_HPP

#include <QtDebug>
#include "ParsingTreeEntryPoint.hpp"
#include "../Types/ParsingTreeValue.hpp"
#include "ParsingTreeKeywordType.hpp"
#include "../Memory/MemoryManagement.hpp"

struct ParsingTreeKeyword: public ParsingTreeEntryPoint
{
    ParsingTreeKeyword();

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory);

    ParsingTreeKeywordType type;
    ParsingTreeValue *value;
};

#endif // PARSINGTREEKEYWORD_HPP
