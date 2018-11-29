#include "ParsingTreeValue.hpp"
#include "../Exceptions/InvalidOperationException.hpp"
#include "../Lexer/TokenStrings.hpp"

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
    throw InvalidOperationException("Unsupported '" CS_LEXER_PLUS_OPERATOR "' operation", "", "", -1, -1);
}

ParsingTreeValue* ParsingTreeValue::remove(ParsingTreeValue* other)
{
    Q_UNUSED(other);
    throw InvalidOperationException("Unsupported '" CS_LEXER_MINUS_OPERATOR "' operation", "", "", -1, -1);
}

ParsingTreeValue* ParsingTreeValue::divide(ParsingTreeValue* other)
{
    Q_UNUSED(other);
    throw InvalidOperationException("Unsupported '" CS_LEXER_DIVIDE_OPERATOR "' operation", "", "", -1, -1);
}

ParsingTreeValue* ParsingTreeValue::multiply(ParsingTreeValue* other)
{
    Q_UNUSED(other);
    throw InvalidOperationException("Unsupported '" CS_LEXER_MULTIPLY_OPERATOR "' operation", "", "", -1, -1);
}
