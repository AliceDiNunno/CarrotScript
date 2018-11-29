#include "ParsingTreeValueComparisonType.hpp"
#include "../Lexer/TokenStrings.hpp"

ParsingTreeValueComparisonType comparisonTypeFromToken(Token tkn)
{
    if (tkn.content == CS_LEXER_EQUALEQUAL_OPERATOR)
        return PTVCT_Equals;
    else if (tkn.content == CS_LEXER_NOTEQUAL_OPERATOR)
        return PTVCT_NotEquals;
    else if (tkn.content == CS_LEXER_GREATER_OPERATOR)
        return PTVCT_BiggerThan;
    else if (tkn.content == CS_LEXER_LESSER_OPERATOR)
        return PTVCT_SmallerThan;
    else if (tkn.content == CS_LEXER_GREATEROREQUAL_OPERATOR)
        return PTVCT_BiggerOrEqualsThan;
    else if (tkn.content == CS_LEXER_LESSOREQUAL_OPERATOR)
        return PTVCT_SmallerOrEqualsThan;
    else if (tkn.content == CS_LEXER_AND_OPERATOR)
        return PTVCT_And;
    else if (tkn.content == CS_LEXER_OR_OPERATOR)
        return PTVCT_Or;
    else
    {
        return PTVCT_Unknown;
    }
}
