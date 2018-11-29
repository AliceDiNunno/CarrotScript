#include "ParsingTreeFunctionCall.hpp"
#include "../Memory/MemoryManagement.hpp"
#include "../Memory/ParsingTreeAccessor.hpp"
#include "../Memory/ParsingTreeIdentifier.hpp"

ParsingTreeFunctionCall::ParsingTreeFunctionCall()
{
    debugName = "ParsingTreeFunctionCall";
}

ParsingTreeFunctionCall::~ParsingTreeFunctionCall()
{

}

ParsingTreeValue *ParsingTreeFunctionCall::execute(MemoryManagement *pMemory)
{
    pMemory->enterScope();
    ParsingTreeValue *pResult = pMemory->callFunction(source, arguments);
    pMemory->exitScope();

    executeNext(pMemory);

    return pResult;
}
