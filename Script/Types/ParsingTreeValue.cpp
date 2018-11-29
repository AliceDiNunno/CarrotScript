#include "ParsingTreeValue.hpp"

ParsingTreeValue::ParsingTreeValue()
{
    debugName = "ParsingTreeValue";
}

ParsingTreeValue::~ParsingTreeValue()
{

}

ParsingTreeValue* ParsingTreeValue::add(ParsingTreeValue* other)
{
    Q_UNUSED(other);
    return nullptr; //err;
}

ParsingTreeValue* ParsingTreeValue::remove(ParsingTreeValue* other)
{
    Q_UNUSED(other);
    return nullptr; //err;
}

ParsingTreeValue* ParsingTreeValue::divide(ParsingTreeValue* other)
{
    Q_UNUSED(other);
    return nullptr; //err;
}

ParsingTreeValue* ParsingTreeValue::multiply(ParsingTreeValue* other)
{
    Q_UNUSED(other);
    return nullptr; //err;
}
