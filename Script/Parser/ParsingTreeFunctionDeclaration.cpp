#include "ParsingTreeFunctionDeclaration.hpp"

ParsingTreeFunctionDeclaration::ParsingTreeFunctionDeclaration()
{
    debugName = "ParsingTreeFunctionDeclaration";
}

ParsingTreeValue *ParsingTreeFunctionDeclaration::execute(MemoryManagement *pMemory)
{
    //qDebug() << "Declare function";
    executeNext(pMemory);
    return nullptr;
}
