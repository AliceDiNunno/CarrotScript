#include "ParsingTreeInteger.hpp"
#include "ParsingTreeString.hpp"

ParsingTreeInteger::ParsingTreeInteger()
{
    debugName = "ParsingTreeInteger";
}

ParsingTreeValue *ParsingTreeInteger::execute(MemoryManagement *pMemory)
{
    executeNext(pMemory);
    return this;
}

ParsingTreeInteger *ParsingTreeInteger::makeInteger(int v)
{
    //qDebug() << "IN " << v;
    ParsingTreeInteger *pInt = new ParsingTreeInteger();
    pInt->value = v;
    return pInt;
}

ParsingTreeFloat *ParsingTreeInteger::makeFloat(double v)
{
    //qDebug() << "FL " << v;
    ParsingTreeFloat *pFloat = new ParsingTreeFloat();
    pFloat->value = v;
    return pFloat;
}

ParsingTreeString *ParsingTreeInteger::makeString(QString v)
{
    //qDebug() << "ST " << v;
    ParsingTreeString *pString = new ParsingTreeString();
    pString->value = v;
    return pString;
}

ParsingTreeValue *ParsingTreeInteger::add(ParsingTreeValue* other)
{
    if (ParsingTreeFloat *rightValue = dynamic_cast<ParsingTreeFloat *>(other))
    {
        return makeFloat((double)value + rightValue->value);
    }
    if (ParsingTreeInteger *rightValue = dynamic_cast<ParsingTreeInteger *>(other))
    {
        return makeInteger(value + rightValue->value);
    }
    if (ParsingTreeString *rightValue = dynamic_cast<ParsingTreeString *>(other))
    {
        return makeString(QString("%1%2").arg(value).arg(rightValue->value));
    }
    return nullptr; //err
}

ParsingTreeValue *ParsingTreeInteger::remove(ParsingTreeValue* other)
{
    if (ParsingTreeFloat *rightValue = dynamic_cast<ParsingTreeFloat *>(other))
    {
        return makeFloat((double)value - rightValue->value);
    }
    if (ParsingTreeInteger *rightValue = dynamic_cast<ParsingTreeInteger *>(other))
    {
        return makeInteger(value - rightValue->value);
    }
    return nullptr; //err
}

#include "math.h"

ParsingTreeValue *ParsingTreeInteger::divide(ParsingTreeValue* other)
{
    if (ParsingTreeFloat *rightValue = dynamic_cast<ParsingTreeFloat *>(other))
    {
        return makeFloat((double)value / rightValue->value);
    }
    if (ParsingTreeInteger *rightValue = dynamic_cast<ParsingTreeInteger *>(other))
    {
        double dbl = double(value) / double(rightValue->value);

        if (ceil(dbl) == dbl)
            return makeInteger(dbl);
        return makeFloat(dbl);
    }
    return nullptr; //err
}

ParsingTreeValue *ParsingTreeInteger::multiply(ParsingTreeValue* other)
{
    if (ParsingTreeFloat *rightValue = dynamic_cast<ParsingTreeFloat *>(other))
    {
        return makeFloat((double)value * rightValue->value);
    }
    if (ParsingTreeInteger *rightValue = dynamic_cast<ParsingTreeInteger *>(other))
    {
        return makeInteger(value * rightValue->value);
    }
    return nullptr; //err
}
