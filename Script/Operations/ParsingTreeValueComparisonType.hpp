#ifndef PARSINGTREEVALUECOMPARISONTYPE_HPP
#define PARSINGTREEVALUECOMPARISONTYPE_HPP

#include "../Lexer/Token.hpp"

enum ParsingTreeValueComparisonType
{
    PTVCT_Equals, // ==
    PTVCT_NotEquals, // !=
    PTVCT_BiggerThan, // >
    PTVCT_SmallerThan, // <
    PTVCT_BiggerOrEqualsThan, // >=
    PTVCT_SmallerOrEqualsThan, // <=
    PTVCT_And,
    PTVCT_Or,
    PTVCT_Unknown
};

ParsingTreeValueComparisonType comparisonTypeFromToken(Token tkn);

#endif // PARSINGTREEVALUECOMPARISONTYPE_HPP
