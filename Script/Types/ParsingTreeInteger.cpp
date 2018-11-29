#include "ParsingTreeInteger.hpp"
#include "ParsingTreeString.hpp"
#include "ParsingTreeFloat.hpp"
#include "math.h"

ParsingTreeInteger::ParsingTreeInteger()
{
    debugName = "ParsingTreeInteger";
}

ParsingTreeValue *ParsingTreeInteger::execute(MemoryManagement *pMemory)
{
    executeNext(pMemory);
    return this;
}

ParsingTreeInteger *ParsingTreeInteger::make(int v)
{
    ParsingTreeInteger *pInt = new ParsingTreeInteger();
    pInt->value = v;
    return pInt;
}

ParsingTreeValue *ParsingTreeInteger::add(ParsingTreeValue* other)
{
    if (ParsingTreeFloat *rightValue = dynamic_cast<ParsingTreeFloat *>(other))
    {
        return ParsingTreeFloat::make((double)value + rightValue->value);
    }
    if (ParsingTreeInteger *rightValue = dynamic_cast<ParsingTreeInteger *>(other))
    {
        return make(value + rightValue->value);
    }
    if (ParsingTreeString *rightValue = dynamic_cast<ParsingTreeString *>(other))
    {
        return ParsingTreeString::make(QString("%1%2").arg(value).arg(rightValue->value));
    }
    return ParsingTreeValue::add(other);
}

ParsingTreeValue *ParsingTreeInteger::remove(ParsingTreeValue* other)
{
    if (ParsingTreeFloat *rightValue = dynamic_cast<ParsingTreeFloat *>(other))
    {
        return ParsingTreeFloat::make((double)value - rightValue->value);
    }
    if (ParsingTreeInteger *rightValue = dynamic_cast<ParsingTreeInteger *>(other))
    {
        return make(value - rightValue->value);
    }
    return ParsingTreeValue::remove(other);
}

ParsingTreeValue *ParsingTreeInteger::divide(ParsingTreeValue* other)
{
    if (ParsingTreeFloat *rightValue = dynamic_cast<ParsingTreeFloat *>(other))
    {
        return ParsingTreeFloat::make((double)value / rightValue->value);
    }
    if (ParsingTreeInteger *rightValue = dynamic_cast<ParsingTreeInteger *>(other))
    {
        double dbl = double(value) / double(rightValue->value);

        if (ceil(dbl) == dbl)
            return make(dbl);
        return ParsingTreeFloat::make(dbl);
    }
    return ParsingTreeValue::divide(other);
}

ParsingTreeValue *ParsingTreeInteger::multiply(ParsingTreeValue* other)
{
    if (ParsingTreeFloat *rightValue = dynamic_cast<ParsingTreeFloat *>(other))
    {
        return ParsingTreeFloat::make((double)value * rightValue->value);
    }
    if (ParsingTreeInteger *rightValue = dynamic_cast<ParsingTreeInteger *>(other))
    {
        return make(value * rightValue->value);
    }
    return ParsingTreeValue::multiply(other);
}
