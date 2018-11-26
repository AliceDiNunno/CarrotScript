#include "ParsingTreeString.hpp"
#include "ParsingTreeBoolean.hpp"
#include "ParsingTreeInteger.hpp"
#include "ParsingTreeFloat.hpp"

ParsingTreeString *ParsingTreeString::makeString(QString v)
{
    //qDebug() << "ST " << v;
    ParsingTreeString *pString = new ParsingTreeString();
    pString->value = v;
    return pString;
}

ParsingTreeValue *ParsingTreeString::add(ParsingTreeValue *other)
{
    if (ParsingTreeFloat *rightValue = dynamic_cast<ParsingTreeFloat *>(other))
    {
        return makeString(value.append(QString("%1").arg(rightValue->value)));
    }
    if (ParsingTreeInteger *rightValue = dynamic_cast<ParsingTreeInteger *>(other))
    {
        return makeString(value.append(QString("%1").arg(rightValue->value)));
    }
    if (ParsingTreeBoolean *rightValue = dynamic_cast<ParsingTreeBoolean *>(other))
    {
        return makeString(value.append(QString("%1").arg(rightValue->value)));
    }
    if (ParsingTreeString *rightValue = dynamic_cast<ParsingTreeString *>(other))
    {
        return makeString(value.append(rightValue->value));
    }
    return nullptr; //err
}
