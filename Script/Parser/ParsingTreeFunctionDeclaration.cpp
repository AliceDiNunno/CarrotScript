#include "ParsingTreeFunctionDeclaration.hpp"

ParsingTreeFunctionDeclaration::ParsingTreeFunctionDeclaration()
{
    debugName = "ParsingTreeFunctionDeclaration";
}

ParsingTreeValue *ParsingTreeFunctionDeclaration::execute(MemoryManagement *pMemory)
{
    executeNext(pMemory);
    return nullptr;
}
