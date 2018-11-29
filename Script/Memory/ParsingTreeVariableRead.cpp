#include "ParsingTreeVariabeRead.hpp"

ParsingTreeVariabeRead::ParsingTreeVariabeRead()
{
    debugName = "ParsingTreeVariabeRead";
}

ParsingTreeValue *ParsingTreeVariabeRead::execute(MemoryManagement *pMemory)
{
    executeNext(pMemory);
    return pMemory->readValue(id);
}
