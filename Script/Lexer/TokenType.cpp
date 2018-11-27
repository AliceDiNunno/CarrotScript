#include "TokenType.hpp"

QString tts(TokenType t)
{
    switch (t) {
    case T_Keyword:
        return "T_Keyword";
    case T_Identifier:
        return "T_Identifier";
    case T_StringLitteral:
        return "T_StringLitteral";
    case T_NumericLitteral:
        return "T_NumericLitteral";
    case T_FloatLitteral:
        return "T_FloatLitteral";
    case T_BoolLitteral:
        return "T_BoolLitteral";
    case T_AccessSeparator:
        return "T_AccessSeparator";
    case T_Separator:
        return "T_Separator";
    case T_Assignement:
        return "T_Assignement";
    case T_Operation:
        return "T_Operation";
    case T_Comparison:
        return "T_Comparison";
    case T_ModuleAccess:
        return "T_ModuleAccess";
    case T_EnterArray:
        return "T_EnterArray";
    case T_ExitArray:
        return "T_ExitArray";
    case T_EnterDefineArray:
        return "T_EnterDefineArray";
    case T_ExitDefineArray:
        return "T_ExitDefineArray";
    case T_EnterFunction:
        return "T_EnterFunction";
    case T_ExitFunction:
        return "T_ExitFunction";
    case T_EnterPriority:
        return "T_EnterPriority";
    case T_ExitPriority:
        return "T_ExitPriority";
    case T_ArgumentSeparator:
        return "T_ArgumentSeparator";
    }
    return "T_Unknown";
}

bool isSymbol(TokenType t)
{
    return (t >= T_AccessSeparator && t <= T_ArgumentSeparator);
}
