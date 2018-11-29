#ifndef PARSINGTREEVARIABEREAD_HPP
#define PARSINGTREEVARIABEREAD_HPP

#include "../Types/ParsingTreeValue.hpp"
#include "ParsingTreeAccessor.hpp"
#include "MemoryManagement.hpp"

struct ParsingTreeVariabeRead: public ParsingTreeValue
{
    ParsingTreeVariabeRead();
    ParsingTreeValue *execute(MemoryManagement *pMemory);

    ParsingTreeAccessor *id;
};

#endif // PARSINGTREEVARIABEREAD_HPP
