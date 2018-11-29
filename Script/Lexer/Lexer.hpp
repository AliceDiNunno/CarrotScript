#ifndef LEXER_HPP
#define LEXER_HPP

#include <QString>
#include <QRegularExpression>
#include <QStack>
#include "Token.hpp"
#include "TokenizeItem.hpp"

class Lexer
{
public:
    Lexer();

    void parseFile(QByteArray );
    Token tokenize(QByteArray );
    QList<QList<Token>> getAllTokens();

public:
    static bool isAcceptedSymbol(QChar c);
    static bool shouldReadNextSymbol(QChar c);
    static bool isTokenEnter(TokenType t);
    static bool isTokenExit(TokenType t);
    static bool areTokenPair(TokenType a, TokenType b);
    static bool isBoolLitteral(QByteArray );
    static bool isAssignmentOperator(QByteArray );
    static bool isOperationOperator(QByteArray );
    static bool isComparisonOperator(QByteArray );
    static bool isFunction(QList<Token> tokens);

private:
    QList<Token> parseLine(QByteArray , int line);
    Token readToken(QByteArray, int line, int *column, Token *lastToken);
    QPair<TokenType, QByteArray> readIdentifier(QByteArray currentLine, int line, int *column);
    QPair<TokenType, QByteArray> readNumber(QByteArray currentLine, int line, int *column);
    QPair<TokenType, QByteArray> readSymbol(QByteArray, int line, int *column, Token *lastToken);
    QPair<TokenType, QByteArray> readQuote(QByteArray, int line, int *column);
    void skipSpaces(QByteArray, int *column);
    static TokenType getEnterExitPair(TokenType t);

private:
    TokenType getSymbol(QByteArray , Token *lastToken);
    bool isKeyword(QByteArray );

private:
    QList<TokenizeItem> availableTokens;

private:
    //Order is:
    //Lines<Tokens<Token>>
    QList<QList<Token>> tokenizedLines;
    QStack<TokenType> separatorPriority;
};

#endif // LEXER_HPP
