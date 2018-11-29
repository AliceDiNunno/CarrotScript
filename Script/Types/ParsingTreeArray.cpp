#include "ParsingTreeArray.hpp"

ParsingTreeArray::ParsingTreeArray()
{
    debugName = "ParsingTreeArray";
}

ParsingTreeValue *ParsingTreeArray::execute(MemoryManagement *)
{
    return this;
}
