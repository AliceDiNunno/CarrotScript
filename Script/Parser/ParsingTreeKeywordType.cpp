#include "ParsingTreeKeywordType.hpp"
#include "../Lexer/TokenStrings.hpp"

ParsingTreeKeywordType getKeywordType(QByteArray keyword)
{
    if (keyword == CS_LEXER_IF_KEYWORD)
        return PTKT_If;
    else if (keyword == CS_LEXER_ELSE_KEYWORD)
        return PTKT_Else;
    else if (keyword == CS_LEXER_WHILE_KEYWORD)
        return PTKT_While;
    else if (keyword == CS_LEXER_END_KEYWORD)
        return PTKT_End;
    else if (keyword == CS_LEXER_REQUIRE_KEYWORD)
        return PTKT_Require;
    else if (keyword == CS_LEXER_RETURN_KEYWORD)
        return PTKT_Return;
    return PTKT_Unknown;
}
