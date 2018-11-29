#include "ParsingTreeString.hpp"
#include "ParsingTreeBoolean.hpp"
#include "ParsingTreeInteger.hpp"
#include "ParsingTreeFloat.hpp"

ParsingTreeString::ParsingTreeString()
{
    debugName = "ParsingTreeString";
}

ParsingTreeValue *ParsingTreeString::execute(MemoryManagement *pMem)
{
    executeNext(pMem);
    return this;
}

ParsingTreeString *ParsingTreeString::make(QString v)
{
    ParsingTreeString *pString = new ParsingTreeString();
    pString->value = v;
    return pString;
}

ParsingTreeValue *ParsingTreeString::add(ParsingTreeValue *other)
{
    if (ParsingTreeFloat *rightValue = dynamic_cast<ParsingTreeFloat *>(other))
    {
        return make(value.append(QString("%1").arg(rightValue->value)));
    }
    if (ParsingTreeInteger *rightValue = dynamic_cast<ParsingTreeInteger *>(other))
    {
        return make(value.append(QString("%1").arg(rightValue->value)));
    }
    if (ParsingTreeBoolean *rightValue = dynamic_cast<ParsingTreeBoolean *>(other))
    {
        return make(value.append(QString("%1").arg(rightValue->value)));
    }
    if (ParsingTreeString *rightValue = dynamic_cast<ParsingTreeString *>(other))
    {
        return make(value.append(rightValue->value));
    }
    return nullptr; //err
}
