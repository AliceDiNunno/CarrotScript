#include "ParsingTreeBoolean.hpp"
#include "ParsingTreeInteger.hpp"

ParsingTreeBoolean::ParsingTreeBoolean()
{
    debugName = "ParsingTreeBoolean";
}

ParsingTreeBoolean *ParsingTreeBoolean::make(bool v)
{
    ParsingTreeBoolean *pBool = new ParsingTreeBoolean();
    pBool->value = v;
    return pBool;
}

ParsingTreeValue *ParsingTreeBoolean::execute(MemoryManagement *pMemory)
{
    executeNext(pMemory);
    return this;
}

ParsingTreeValue* ParsingTreeBoolean::add(ParsingTreeValue* other)
{
    if (ParsingTreeBoolean *rightValue = dynamic_cast<ParsingTreeBoolean *>(other))
    {
        return make(value + rightValue->value);
    }
    if (ParsingTreeInteger *rightValue = dynamic_cast<ParsingTreeInteger *>(other))
    {
        bool rightBool = rightValue->value > 0;
        return make(value + rightBool);
    }
    return ParsingTreeValue::add(other);
}

ParsingTreeValue* ParsingTreeBoolean::remove(ParsingTreeValue* other)
{
    if (ParsingTreeBoolean *rightValue = dynamic_cast<ParsingTreeBoolean *>(other))
    {
        return make(value - rightValue->value);
    }
    if (ParsingTreeInteger *rightValue = dynamic_cast<ParsingTreeInteger *>(other))
    {
        bool rightBool = rightValue->value > 0;
        return make(value - rightBool);
    }
    return ParsingTreeValue::remove(other);
}
