#include "ParsingTreeKeyword.hpp"

ParsingTreeKeyword::ParsingTreeKeyword()
{
    debugName = "ParsingTreeKeyword";
}

ParsingTreeValue *ParsingTreeKeyword::execute(MemoryManagement *pMemory)
{
    if (type == PTKT_End)
    {
        pMemory->exitScope();
    }
    executeNext(pMemory);
    return nullptr;
}
