#ifndef PARSINGTREEACCESSOR_HPP
#define PARSINGTREEACCESSOR_HPP

#include "ParsingTreeIdentifier.hpp"

struct ParsingTreeAccessor: public ParsingTreeIdentifier
{
    ParsingTreeAccessor()
    {
        debugName = "ParsingTreeAccessor";
    }
    ParsingTreeValue *execute(MemoryManagement *pMemory);
    ParsingTreeAccessor *child = nullptr; // User -> info -> displayName
};

#endif // PARSINGTREEACCESSOR_HPP
