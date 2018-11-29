#include "ParsingTreeFloat.hpp"
#include "ParsingTreeInteger.hpp"
#include "ParsingTreeString.hpp"

ParsingTreeFloat::ParsingTreeFloat()
{
    debugName = "ParsingTreeFloat";
}

ParsingTreeValue *ParsingTreeFloat::execute(MemoryManagement *pMemory)
{
    executeNext(pMemory);
    return this;
}

ParsingTreeFloat *ParsingTreeFloat::make(double v)
{
    ParsingTreeFloat *pFloat = new ParsingTreeFloat();
    pFloat->value = v;
    return pFloat;
}

ParsingTreeValue* ParsingTreeFloat::add(ParsingTreeValue* other)
{
    if (ParsingTreeFloat *rightValue = dynamic_cast<ParsingTreeFloat *>(other))
    {
        return make(value + rightValue->value);
    }
    if (ParsingTreeInteger *rightValue = dynamic_cast<ParsingTreeInteger *>(other))
    {
        return make(value + (double)rightValue->value);
    }
    if (ParsingTreeString *rightValue = dynamic_cast<ParsingTreeString *>(other))
    {
        return ParsingTreeString::make(QString("%1%2").arg(value).arg(rightValue->value));
    }
    return ParsingTreeValue::add(other);
}

ParsingTreeValue* ParsingTreeFloat::remove(ParsingTreeValue* other)
{
    if (ParsingTreeFloat *rightValue = dynamic_cast<ParsingTreeFloat *>(other))
    {
        return make(value - rightValue->value);
    }
    if (ParsingTreeInteger *rightValue = dynamic_cast<ParsingTreeInteger *>(other))
    {
        return make(value - (double)rightValue->value);
    }
    return ParsingTreeValue::remove(other);
}

ParsingTreeValue* ParsingTreeFloat::divide(ParsingTreeValue* other)
{
    if (ParsingTreeFloat *rightValue = dynamic_cast<ParsingTreeFloat *>(other))
    {
        return make(value / rightValue->value);
    }
    if (ParsingTreeInteger *rightValue = dynamic_cast<ParsingTreeInteger *>(other))
    {
        return make(value / (double)rightValue->value);
    }
    return ParsingTreeValue::divide(other);
}

ParsingTreeValue* ParsingTreeFloat::multiply(ParsingTreeValue* other)
{
    if (ParsingTreeFloat *rightValue = dynamic_cast<ParsingTreeFloat *>(other))
    {
        return make(value * rightValue->value);
    }
    if (ParsingTreeInteger *rightValue = dynamic_cast<ParsingTreeInteger *>(other))
    {
        return make(value * (double)rightValue->value);
    }
    return ParsingTreeValue::multiply(other);
}
