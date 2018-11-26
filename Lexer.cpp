#include <QStringList>
#include <QRegularExpression>
#include "Lexer.hpp"
#include <QDebug>
#include "UnknownTokenException.hpp"

Lexer::Lexer()
{
    regexpPureNumber = QRegularExpression("^([0-9]*)$");
    regexpPureString = QRegularExpression("^\"(.*?)\"$");
    regexpStartsWithNumber = QRegularExpression("^([0-9].*)$");
    regexpIdentifierAcceptedCharacters = QRegularExpression("^[a-zA-Z0-9_]*$");
    regexpFloat = QRegularExpression("^[\\d]+\\.[\\d]+$");
}

bool Lexer::isKeyword(QByteArray aElement)
{
    QStringList keywords = {"if", "else", "while", "end", "require", "func", "return"};
    return keywords.contains(aElement);
}

bool Lexer::isIdentifier(QByteArray aElement)
{
    QRegularExpressionMatch acceptedCharacterMatch = regexpIdentifierAcceptedCharacters.match(aElement);
    QRegularExpressionMatch startsWithNumber = regexpStartsWithNumber.match(aElement);
    return (acceptedCharacterMatch.hasMatch() && !startsWithNumber.hasMatch());
}

bool Lexer::isStringLitteral(QByteArray aElement)
{
    QRegularExpressionMatch matchString = regexpPureString.match(aElement);
    return matchString.hasMatch();
}

bool Lexer::isFloatLitteral(QByteArray aElement)
{
    QRegularExpressionMatch matchFloat = regexpFloat.match(aElement);
    return matchFloat.hasMatch();
}

bool Lexer::isNumericLitteral(QByteArray aElement)
{
    QRegularExpressionMatch matchNumber = regexpPureNumber.match(aElement);
    return matchNumber.hasMatch();
}

bool Lexer::isBoolLitteral(QByteArray aElement)
{
    QStringList keywords = {"true", "false"};
    return keywords.contains(aElement);
}

bool Lexer::isAccessSeparator(QByteArray aElement)
{
    QStringList separator = {"[", "]", "."};
    return separator.contains(aElement);
}

bool Lexer::isSeparator(QByteArray aElement)
{
    QStringList separator = {"(", ")", ","};
    return separator.contains(aElement);
}

bool Lexer::isAssignmentOpererator(QByteArray aElement)
{
    QStringList operators = {"-=", "+=", "++", "--", "*=", "/=", "="};
    return operators.contains(aElement);
}

bool Lexer::isOperationOperator(QByteArray aElement)
{
    QStringList operators = {"+", "-", "/", "*"};
    return operators.contains(aElement);
}

bool Lexer::isComparisonOperator(QByteArray aElement)
{
    QStringList operators = {"==", "!=", "<=", ">=", "<", ">", "&&", "||", "!"};
    return operators.contains(aElement);
}

void Lexer::skipSpaces(QByteArray currentLine, int *column)
{
    while (*column < currentLine.count() && (currentLine.at(*column) == ' ' || currentLine.at(*column) == '\t' || currentLine.at(*column) == '\r'))
    {
        *column = *column + 1;
    }
}

QPair<TokenType, QByteArray> Lexer::readQuote(QByteArray currentLine, int line, int *column)
{
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
        if (currentChar == '"' && lastChar != '\\' && currentQuote.count() > 1)
            continueFetching = false;
        lastChar = currentChar;
    }
    currentQuote.remove(0, 1);
    currentQuote.remove(currentQuote.length() - 1, 1);
    return {T_StringLitteral, currentQuote};
}

bool Lexer::isAcceptedSymbol(QChar c)
{
    QList<QChar> acceptedSymbols = {'[', ']', '(', ')', ',', '"', '.', '!', '=', '<', '>', '&', '|', '+', '-', '*', '/'};
    return acceptedSymbols.contains(c);
}

QPair<TokenType, QByteArray> Lexer::readIdentifier(QByteArray currentLine, int line, int *column)
{
    TokenType currentToken;
    QByteArray currentIdentifier;
    QChar currentChar;
    do
    {
        if ((*column) >= currentLine.count())
            break;
        currentChar = currentLine.at(*column);
        if (currentChar.isLetterOrNumber() || currentChar == '_')
        {
            currentIdentifier.append(currentChar);
            *column = *column + 1;
        }
    }
    while (currentChar.isLetterOrNumber() || currentChar == '_');

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
    TokenType currentToken;
    QByteArray currentIdentifier;
    QChar currentChar;
    do
    {
        if ((*column) >= currentLine.count())
            break;
        currentChar = currentLine.at(*column);
        if (currentChar.isNumber() ||
           (currentChar == "-" && currentIdentifier.isEmpty()))
        {
            currentIdentifier.append(currentChar);
            *column = *column + 1;
        }
    }
    while (currentChar.isNumber() ||
           (currentIdentifier == "-"));
    currentToken = T_NumericLitteral;

    if (currentChar == '.')
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
            throw UnknownTokenException();
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
        if (currentchar == '#')
        {
            return t;
        }
        else if (currentchar == '"')
        {
            currentToken = readQuote(currentLine, line, column);
        }
        else if (currentchar.isLetter() || currentchar == '_')
        {
            currentToken = readIdentifier(currentLine, line, column);
        }
        else if (currentchar.isNumber() ||
                (currentchar == '-' && (*column) + 1 < currentLine.count() && QChar(currentLine.at((*column) + 1)).isNumber()))
        {
            currentToken = readNumber(currentLine, line, column);
        }
        else if (isAcceptedSymbol(currentchar))
        {
            currentToken = readSymbol(currentLine, line, column, lastToken);
        }
        else
        {
            throw UnknownTokenException();
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
    if (isAssignmentOpererator(symbol))
        return T_Assignement;
    else if (isAssignmentOpererator(symbol))
        return T_Unknown;
    if (isOperationOperator(symbol))
        return T_Operation;
    if (symbol == "." && lastToken->type == T_Identifier)
        return T_ModuleAccess;
    if (symbol == ",")
        return T_ArgumentSeparator;

    TokenType t = T_Unknown;
    if (symbol == "[")
    {
        if (lastToken->type == T_Identifier || lastToken->type == T_StringLitteral)
            t = T_EnterArray;
        else if (lastToken->type == T_Assignement)
            t = T_EnterDefineArray;
    }
    if (symbol == "(")
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

    if (symbol == "]")
    {
        if (separatorPriority.count() <= 0)
            throw UnknownTokenException();

        if (separatorPriority.top() != T_EnterArray && separatorPriority.top() != T_EnterDefineArray)
            throw UnknownTokenException();

        TokenType t =  separatorPriority.pop();
        if (t == T_EnterArray)
            return T_ExitArray;
        else
            return T_ExitDefineArray;
    }
    if (symbol == ")")
    {
        if (separatorPriority.count() <= 0)
            throw UnknownTokenException();

        if (separatorPriority.top() != T_EnterFunction && separatorPriority.top() != T_EnterPriority)
            throw UnknownTokenException();

        TokenType t = separatorPriority.pop();
        if (t == T_EnterFunction)
            return T_ExitFunction;
        else
            return T_ExitPriority;
    }
    return T_Unknown;
}

bool shouldReadNextSymbol(QChar c)
{
    QList<QChar> accepted = {'-', '+', '*', '/', '!', '<', '>', '&', '|', '!', '='};
    return accepted.contains(c);
}

QPair<TokenType, QByteArray> Lexer::readSymbol(QByteArray currentLine, int line, int *column, Token *lastToken)
{
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
        throw UnknownTokenException();
    }

    return {t, symbol};
}

QList<Token> Lexer::parseLine(QByteArray currentLine, int line)
{
    QByteArray current;
    QList<Token> lineTokens;

   //qDebug() << "parse: " << currentLine;

    if (currentLine.startsWith("#"))
        return lineTokens;

    int column = 0;

    Token t;
    t.type = T_Unknown;
    do
    {
        //qDebug() << "read tok";
        t = readToken(currentLine, line, &column, &t);
        if (t.type != T_EndOfLine)
            lineTokens.append(t);
    }
    while(t.type != T_EndOfLine);
    return lineTokens;
}

void Lexer::parseFile(QByteArray content)
{
    QList<QByteArray> lines = content.split('\n');

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
