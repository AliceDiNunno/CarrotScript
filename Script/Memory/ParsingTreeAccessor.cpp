#include "ParsingTreeAccessor.hpp"
#include "MemoryManagement.hpp"

ParsingTreeAccessor::ParsingTreeAccessor()
{
    debugName = "ParsingTreeAccessor";
}

ParsingTreeValue *ParsingTreeAccessor::execute(MemoryManagement *pMemory)
{
    Q_UNUSED(pMemory);
    return this;
}
