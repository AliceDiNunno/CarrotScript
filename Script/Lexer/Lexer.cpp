#include <QStringList>
#include <QRegularExpression>
#include "Lexer.hpp"
#include "TokenStrings.hpp"
#include "../Exceptions/UnknownTokenException.hpp"

Lexer::Lexer()
{
    availableTokens = QList<TokenizeItem>();
    tokenizedLines = QList<QList<Token>>();
    separatorPriority = QStack<TokenType>();
}

bool Lexer::isKeyword(QByteArray aElement)
{
    QStringList keywords = {CS_LEXER_IF_KEYWORD,
                            CS_LEXER_ELSE_KEYWORD,
                            CS_LEXER_WHILE_KEYWORD,
                            CS_LEXER_END_KEYWORD,
                            CS_LEXER_REQUIRE_KEYWORD,
                            CS_LEXER_FUNC_KEYWORD,
                            CS_LEXER_RETURN_KEYWORD};
    return keywords.contains(aElement);
}

bool Lexer::isBoolLitteral(QByteArray aElement)
{
    QStringList keywords = {CS_LEXER_TRUE_BOOL,
                            CS_LEXER_FALSE_BOOL};
    return keywords.contains(aElement);
}

bool Lexer::isAssignmentOperator(QByteArray aElement)
{
    QStringList operators = {CS_LEXER_MINUSEQUAL_OPERATOR,
                             CS_LEXER_PLUSEQUAL_OPERATOR,
                             CS_LEXER_MULTIPLYEQUAL_OPERATOR,
                             CS_LEXER_DIVIDEEQUAL_OPERATOR,
                             CS_LEXER_PLUSPLUS_OPERATOR,
                             CS_LEXER_MINUSMINUS_OPERATOR,
                             CS_LEXER_EQUAL_OPERATOR};
    return operators.contains(aElement);
}

bool Lexer::isOperationOperator(QByteArray aElement)
{
    QStringList operators = {CS_LEXER_PLUS_OPERATOR,
                             CS_LEXER_MINUS_OPERATOR,
                             CS_LEXER_DIVIDE_OPERATOR,
                             CS_LEXER_MULTIPLY_OPERATOR};
    return operators.contains(aElement);
}

bool Lexer::isComparisonOperator(QByteArray aElement)
{
    QStringList operators = {CS_LEXER_EQUALEQUAL_OPERATOR,
                             CS_LEXER_NOTEQUAL_OPERATOR,
                             CS_LEXER_LESSOREQUAL_OPERATOR,
                             CS_LEXER_GREATEROREQUAL_OPERATOR,
                             CS_LEXER_LESSER_OPERATOR,
                             CS_LEXER_GREATER_OPERATOR,
                             CS_LEXER_AND_OPERATOR,
                             CS_LEXER_OR_OPERATOR,
                             CS_LEXER_NOT_OPERATOR};
    return operators.contains(aElement);
}

bool Lexer::isTokenEnter(TokenType t)
{
    return (t == T_EnterPriority ||
            t == T_EnterArray ||
            t == T_EnterDefineArray ||
            t == T_EnterFunction);
}

bool Lexer::isTokenExit(TokenType t)
{
    return (t == T_ExitPriority ||
            t == T_ExitArray ||
            t == T_ExitDefineArray ||
            t == T_ExitFunction);
}

TokenType Lexer::getEnterExitPair(TokenType t)
{
    if (t == T_EnterPriority)
        return T_ExitPriority;
    if (t == T_ExitPriority)
        return T_EnterPriority;

    if (t == T_EnterArray)
        return T_ExitArray;
    if (t == T_ExitArray)
        return T_EnterArray;

    if (t == T_EnterDefineArray)
        return T_ExitDefineArray;
    if (t == T_ExitDefineArray)
        return T_EnterDefineArray;

    if (t == T_EnterFunction)
        return T_ExitFunction;
    if (t == T_ExitFunction)
        return T_EnterFunction;
    return T_Unknown;
}

bool Lexer::areTokenPair(TokenType a, TokenType b)
{
    if ((a == T_EnterPriority && b == T_ExitPriority) ||
            (a == T_ExitPriority && b == T_EnterPriority))
        return true;
    if ((a == T_EnterArray && b == T_ExitArray) ||
            (a == T_ExitArray && b == T_EnterArray))
        return true;
    if ((a == T_EnterDefineArray && b == T_ExitDefineArray) ||
            (a == T_ExitDefineArray && b == T_EnterDefineArray))
        return true;
    if ((a == T_EnterFunction && b == T_ExitFunction) ||
            (a == T_ExitFunction && b == T_EnterFunction))
        return true;
    return false;
}

bool Lexer::isFunction(QList<Token> tokens)
{
    for (int iToken = 0; iToken < tokens.count(); iToken++)
    {
        Token tok = tokens.at(iToken);
        if (tok.type == T_Identifier || tok.type == T_ModuleAccess || tok.type == T_EnterArray)
        {
            continue;
        }
        if (iToken + 1 == tokens.count() && tokens.at(iToken).type == T_EnterFunction)
        {
            return true;
        }
    }
    return false;
}

bool Lexer::isAcceptedSymbol(QChar c)
{
    QList<QChar> acceptedSymbols = {'[', ']', '(', ')', ',', '"', '.', '!', '=', '<', '>', '&', '|', '+', '-', '*', '/'};
    return acceptedSymbols.contains(c);
}

bool Lexer::shouldReadNextSymbol(QChar c)
{
    QList<QChar> accepted = {'-', '+', '*', '/', '!', '<', '>', '&', '|', '='};
    return accepted.contains(c);
}

void Lexer::skipSpaces(QByteArray currentLine, int *column)
{
    while (*column < currentLine.count() && (currentLine.at(*column) == CS_LEXER_SPACE_CHARACTER || currentLine.at(*column) == CS_LEXER_TAB_CHARACTER || currentLine.at(*column) == CS_LEXER_LINEFEED_CHARACTER))
    {
        *column = *column + 1;
    }
}

QPair<TokenType, QByteArray> Lexer::readQuote(QByteArray currentLine, int line, int *column)
{
    Q_UNUSED(line);

    QByteArray currentQuote = "";
    QChar lastChar = QChar();
    QChar currentChar = QChar();
    bool continueFetching = true;
    while (continueFetching)
    {
        if ((*column) >= currentLine.count())
            break;
        currentChar = currentLine.at(*column);
        currentQuote.append(currentChar);
        *column = *column + 1;
        if (currentChar == CS_LEXER_QUOTE_CHARACTER && lastChar != CS_LEXER_BACKSLASH_CHARACTER && currentQuote.count() > 1)
            continueFetching = false;
        lastChar = currentChar;
    }
    currentQuote.remove(0, 1);
    currentQuote.remove(currentQuote.length() - 1, 1);
    return {T_StringLitteral, currentQuote};
}

QPair<TokenType, QByteArray> Lexer::readIdentifier(QByteArray currentLine, int line, int *column)
{
    Q_UNUSED(line);

    TokenType currentToken;
    QByteArray currentIdentifier;
    QChar currentChar;
    do
    {
        if ((*column) >= currentLine.count())
            break;
        currentChar = currentLine.at(*column);
        if (currentChar.isLetterOrNumber() || currentChar == CS_LEXER_UNDERSCORE_CHARACTER)
        {
            currentIdentifier.append(currentChar);
            *column = *column + 1;
        }
    }
    while (currentChar.isLetterOrNumber() || currentChar == CS_LEXER_UNDERSCORE_CHARACTER);

    if (isKeyword(currentIdentifier))
        currentToken = T_Keyword;
    else if (isBoolLitteral(currentIdentifier))
        currentToken = T_BoolLitteral;
    else
        currentToken = T_Identifier;
    return {currentToken, currentIdentifier};
}

QPair<TokenType, QByteArray> Lexer::readNumber(QByteArray currentLine, int line, int *column)
{
    Q_UNUSED(line);

    TokenType currentToken;
    QByteArray currentIdentifier;
    QChar currentChar;
    do
    {
        if ((*column) >= currentLine.count())
            break;
        currentChar = currentLine.at(*column);
        if (currentChar.isNumber() ||
           (currentChar == CS_LEXER_MINUS_OPERATOR && currentIdentifier.isEmpty()))
        {
            currentIdentifier.append(currentChar);
            *column = *column + 1;
        }
    }
    while (currentChar.isNumber() ||
           (currentIdentifier == CS_LEXER_MINUS_OPERATOR));
    currentToken = T_NumericLitteral;

    if (currentChar == CS_LEXER_FLOAT_SEPARATOR)
    {
        *column = *column + 1;

        if ((*column) >= currentLine.count())
            return {currentToken, currentIdentifier};

        currentIdentifier.append(currentChar);

        if (QChar(currentLine.at(*column)).isNumber())
        {
            QChar currentChar;
            do
            {
                if ((*column) >= currentLine.count())
                    break;

                currentChar = currentLine.at(*column);
                if (currentChar.isNumber())
                {
                    currentIdentifier.append(currentChar);
                    *column = *column + 1;
                }
            }
            while (currentChar.isNumber());
        }
        else
        {
            throw UnknownTokenException("Was expecting number on right-side of float separator", "", currentLine, line, *column);
        }
        currentToken = T_FloatLitteral;
    }

    return {currentToken, currentIdentifier};
}

Token Lexer::readToken(QByteArray currentLine, int line, int *column, Token *lastToken)
{
    if (lastToken->type == T_Unknown)
        lastToken = nullptr;

    Token t;
    t.content = "";
    t.type = T_EndOfLine;
    t.column = *column;
    t.lineNumber = line;
    t.lineStr = currentLine;

    while (*column < currentLine.count())
    {
        skipSpaces(currentLine, column);

        QChar currentchar = currentLine.at(*column);
        QPair<TokenType, QByteArray> currentToken;
        if (currentchar == CS_LEXER_COMMENT_CHARACTER)
        {
            return t;
        }
        else if (currentchar == CS_LEXER_QUOTE_CHARACTER)
        {
            currentToken = readQuote(currentLine, line, column);
        }
        else if (currentchar.isLetter() || currentchar == CS_LEXER_UNDERSCORE_CHARACTER)
        {
            currentToken = readIdentifier(currentLine, line, column);
        }
        else if (currentchar.isNumber() ||
                (currentchar == CS_LEXER_MINUS_OPERATOR && (*column) + 1 < currentLine.count() && QChar(currentLine.at((*column) + 1)).isNumber()))
        {
            currentToken = readNumber(currentLine, line, column);
        }
        else if (isAcceptedSymbol(currentchar))
        {
            currentToken = readSymbol(currentLine, line, column, lastToken);
        }
        else
        {
            throw UnknownTokenException("Unknown token", "", currentLine, line, *column);
        }

        t.type = currentToken.first;
        t.content = currentToken.second;
        return t;
    }
    return t;
}

TokenType Lexer::getSymbol(QByteArray symbol, Token *lastToken)
{
    if (isComparisonOperator(symbol))
        return T_Comparison;
    if (isAssignmentOperator(symbol))
        return T_Assignement;
    else if (isAssignmentOperator(symbol))
        return T_Unknown;
    if (isOperationOperator(symbol))
        return T_Operation;

    if (symbol.count() > 1)
        return T_Unknown;

    QChar charSymbol = symbol.at(0);
    if (charSymbol == CS_LEXER_ACCESSER_SEPARATOR && lastToken->type == T_Identifier)
        return T_ModuleAccess;
    if (charSymbol == CS_LEXER_ARGUMENTS_SEPARATOR)
        return T_ArgumentSeparator;

    TokenType t = T_Unknown;
    if (charSymbol == CS_LEXER_ENTERARRAY_SEPARATOR)
    {
        if (lastToken->type == T_Identifier || lastToken->type == T_StringLitteral)
            t = T_EnterArray;
        else if (lastToken->type == T_Assignement)
            t = T_EnterDefineArray;
    }
    if (charSymbol == CS_LEXER_ENTERFUNCTION_SEPARATOR)
    {
        if (lastToken->type == T_Identifier)
            t = T_EnterFunction;
        else
            t = T_EnterPriority;
    }

    if (t != T_Unknown)
    {
        separatorPriority.push(t);
        return t;
    }

    if (charSymbol == CS_LEXER_EXITARRAY_SEPARATOR)
    {
        if (separatorPriority.count() <= 0)
            throw UnknownTokenException("Can't close function or array without opening one first", "", "", 0, 0);

        if (separatorPriority.top() != T_EnterArray && separatorPriority.top() != T_EnterDefineArray)
            throw UnknownTokenException("Mismatch braces", "", "", 0, 0);

        TokenType t =  separatorPriority.pop();
        if (t == T_EnterArray)
            return T_ExitArray;
        else
            return T_ExitDefineArray;
    }
    if (charSymbol == CS_LEXER_EXITFUNCTION_SEPARATOR)
    {
        if (separatorPriority.count() <= 0)
            throw UnknownTokenException("Can't close function or array without opening one first", "", "", 0, 0);

        if (separatorPriority.top() != T_EnterFunction && separatorPriority.top() != T_EnterPriority)
            throw UnknownTokenException("Mismatch braces", "", "", 0, 0);

        TokenType t = separatorPriority.pop();
        if (t == T_EnterFunction)
            return T_ExitFunction;
        else
            return T_ExitPriority;
    }
    return T_Unknown;
}

QPair<TokenType, QByteArray> Lexer::readSymbol(QByteArray currentLine, int line, int *column, Token *lastToken)
{
    Q_UNUSED(line);

    TokenType t = T_Unknown;
    QByteArray symbol;

    QChar currentToken = currentLine.at(*column);
    symbol.append(currentToken);
    *column = *column + 1;
    if (shouldReadNextSymbol(currentToken))
    {
        QChar currentToken = currentLine.at(*column);
        symbol.append(currentToken);
    }

    t = getSymbol(symbol, lastToken);
    if (t == T_Unknown && symbol.length() == 2)
    {
        symbol.remove(1, 1);
        t = getSymbol(symbol, lastToken);
    }
    else if (symbol.length() == 2)
    {
        *column = *column + 1;
    }

    if (t == T_Unknown)
    {
        throw UnknownTokenException("Unknown token", "", currentLine, line, *column);
    }

    return {t, symbol};
}

QList<Token> Lexer::parseLine(QByteArray currentLine, int line)
{
    QByteArray current;
    QList<Token> lineTokens;

    if (currentLine.startsWith(CS_LEXER_COMMENT_CHARACTER))
        return lineTokens;

    int column = 0;

    Token t;
    t.type = T_Unknown;
    do
    {
        t = readToken(currentLine, line, &column, &t);
        if (t.type != T_EndOfLine)
            lineTokens.append(t);
    }
    while(t.type != T_EndOfLine);
    return lineTokens;
}

void Lexer::parseFile(QByteArray content)
{
    QList<QByteArray> lines = content.split(CS_LEXER_CARRIAGERETURN_CHARACTER);

    tokenizedLines = QList<QList<Token>>();
    for (int iLine = 0; iLine < lines.count(); iLine++)
    {
        QByteArray currentLine = lines.at(iLine);
        QList<Token> lineTokens = parseLine(currentLine, iLine);
        if (!lineTokens.isEmpty())
            tokenizedLines.append(lineTokens);
    }
}

QList<QList<Token>> Lexer::getAllTokens()
{
    return tokenizedLines;
}
