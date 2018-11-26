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

ParsingTreeFloat *ParsingTreeFloat::makeFloat(double v)
{
    //qDebug() << "FL " << v;
    ParsingTreeFloat *pFloat = new ParsingTreeFloat();
    pFloat->value = v;
    //qDebug() << pFloat->value;
    return pFloat;
}

ParsingTreeString *ParsingTreeFloat::makeString(QString v)
{
    //qDebug() << "ST " << v;
    ParsingTreeString *pString = new ParsingTreeString();
    pString->value = v;
    return pString;
}

ParsingTreeValue* ParsingTreeFloat::add(ParsingTreeValue* other)
{
    if (ParsingTreeFloat *rightValue = dynamic_cast<ParsingTreeFloat *>(other))
    {
        return makeFloat(value + rightValue->value);
    }
    if (ParsingTreeInteger *rightValue = dynamic_cast<ParsingTreeInteger *>(other))
    {
        return makeFloat(value + (double)rightValue->value);
    }
    if (ParsingTreeString *rightValue = dynamic_cast<ParsingTreeString *>(other))
    {
        return makeString(QString("%1%2").arg(value).arg(rightValue->value));
    }
    return nullptr; //err
}

ParsingTreeValue* ParsingTreeFloat::remove(ParsingTreeValue* other)
{
    if (ParsingTreeFloat *rightValue = dynamic_cast<ParsingTreeFloat *>(other))
    {
        return makeFloat(value - rightValue->value);
    }
    if (ParsingTreeInteger *rightValue = dynamic_cast<ParsingTreeInteger *>(other))
    {
        return makeFloat(value - (double)rightValue->value);
    }
    return nullptr; //err
}

ParsingTreeValue* ParsingTreeFloat::divide(ParsingTreeValue* other)
{
    if (ParsingTreeFloat *rightValue = dynamic_cast<ParsingTreeFloat *>(other))
    {
        return makeFloat(value / rightValue->value);
    }
    if (ParsingTreeInteger *rightValue = dynamic_cast<ParsingTreeInteger *>(other))
    {
        return makeFloat(value / (double)rightValue->value);
    }
    return nullptr; //err
}

ParsingTreeValue* ParsingTreeFloat::multiply(ParsingTreeValue* other)
{
    if (ParsingTreeFloat *rightValue = dynamic_cast<ParsingTreeFloat *>(other))
    {
        return makeFloat(value * rightValue->value);
    }
    if (ParsingTreeInteger *rightValue = dynamic_cast<ParsingTreeInteger *>(other))
    {
        return makeFloat(value * (double)rightValue->value);
    }
    return nullptr; //err
}
