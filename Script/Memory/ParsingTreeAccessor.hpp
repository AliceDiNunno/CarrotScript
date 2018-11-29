#ifndef PARSINGTREEACCESSOR_HPP
#define PARSINGTREEACCESSOR_HPP

#include "ParsingTreeIdentifier.hpp"

class MemoryManagement;
struct ParsingTreeAccessor: public ParsingTreeIdentifier
{
    ParsingTreeAccessor();
    ParsingTreeValue *execute(MemoryManagement *pMemory);
    ParsingTreeAccessor *child = nullptr; // User -> info -> displayName
};

#endif // PARSINGTREEACCESSOR_HPP
