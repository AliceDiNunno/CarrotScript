#include "ParsingTreeIdentifier.hpp"
ParsingTreeIdentifier::ParsingTreeIdentifier()
{
    debugName = "ParsingTreeIdentifier";
}

ParsingTreeValue *ParsingTreeIdentifier::execute(MemoryManagement *pMemory)
{
    executeNext(pMemory);
    return this;
}
