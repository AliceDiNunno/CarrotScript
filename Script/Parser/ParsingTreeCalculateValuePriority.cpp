#include "ParsingTreeCalculateValuePriority.hpp"
#include "../Lexer/TokenStrings.hpp"

ParsingTreeCalculateValuePriority getPrecedenceFromToken(Token t)
{
    if (t.type == T_EnterPriority)
        return PTCVP_Parenthesis;
    else if (t.type == T_Operation && (t.content == CS_LEXER_PLUS_OPERATOR ||
                                       t.content == CS_LEXER_MINUS_OPERATOR))
        return PTCVP_PlusMinus;
    else if (t.type == T_Operation && (t.content == CS_LEXER_MULTIPLY_OPERATOR ||
                                       t.content == CS_LEXER_DIVIDE_OPERATOR))
        return PTCVP_MultiplyDivide;
    else if (t.type == T_Comparison && t.content == CS_LEXER_AND_OPERATOR)
        return PTCVP_And;
    else if (t.type == T_Comparison && t.content == CS_LEXER_OR_OPERATOR)
        return PTCVP_Or;
    else if (t.type == T_Comparison)
        return PTCVP_Comparison;
    return PTCVP_Unsupported;
}
