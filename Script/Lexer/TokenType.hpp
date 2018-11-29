#ifndef TOKENTYPE_HPP
#define TOKENTYPE_HPP

#include <QString>

enum TokenType
{
    T_Keyword, //0
    T_Identifier,
    T_StringLitteral,
    T_NumericLitteral,
    T_FloatLitteral,
    T_BoolLitteral, //5
    T_AccessSeparator,
    T_Separator,
    T_Assignement,
    T_Operation,
    T_Comparison, //10
    T_ModuleAccess,
    /////////////
    T_EnterArray,
    T_ExitArray,
    T_EnterDefineArray,
    T_ExitDefineArray, //15
    T_EnterFunction,
    T_ExitFunction,
    T_EnterPriority,
    T_ExitPriority,
    T_ArgumentSeparator, //20

    //Other
    T_Unknown,
    T_EndOfLine,
};

extern QString tokenToString(TokenType t);
extern bool isSymbol(TokenType t);
extern QByteArray contentFromTokenType(TokenType t);

#endif // TOKENTYPE_HPP
