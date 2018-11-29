#ifndef PARSINGTREECOMPARISON_HPP
#define PARSINGTREECOMPARISON_HPP

#include "../Types/ParsingTreeBoolean.hpp"
#include "../Types/ParsingTreeValue.hpp"
#include "ParsingTreeValueComparisonType.hpp"
#include "../Memory/MemoryManagement.hpp"

struct ParsingTreeComparison: public ParsingTreeValue
{
    ParsingTreeComparison();

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory);

    ParsingTreeValue *left;
    ParsingTreeValueComparisonType type;
    ParsingTreeValue *right;
    bool successOnFailure;
};

#endif // PARSINGTREECOMPARISON_HPP
