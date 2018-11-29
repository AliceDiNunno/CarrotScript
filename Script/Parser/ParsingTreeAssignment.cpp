#include "ParsingTreeAssignment.hpp"
#include "../Memory/MemoryManagement.hpp"

ParsingTreeAssignment::ParsingTreeAssignment()
{
    debugName = "ParsingTreeAssignment";
}

ParsingTreeValue *ParsingTreeAssignment::execute(MemoryManagement *pMemory)
{
    pMemory->setValue(to, from->execute(pMemory));

    executeNext(pMemory);

    return nullptr;
}
