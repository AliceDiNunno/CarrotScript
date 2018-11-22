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

private:
    QList<Token> parseLine(QByteArray , int line);
    Token readToken(QByteArray, int line, int *column, Token *lastToken);
    QPair<TokenType, QByteArray> readIdentifier(QByteArray currentLine, int line, int *column);
    QPair<TokenType, QByteArray> readNumber(QByteArray currentLine, int line, int *column);
    QPair<TokenType, QByteArray> readSymbol(QByteArray, int line, int *column, Token *lastToken);
    QPair<TokenType, QByteArray> readQuote(QByteArray, int line, int *column);
    void skipSpaces(QByteArray, int *column);
    bool isAcceptedSymbol(QChar c);

private:
    TokenType getSymbol(QByteArray , Token *lastToken);

    bool isKeyword(QByteArray );
    bool isIdentifier(QByteArray );
    bool isStringLitteral(QByteArray );
    bool isFloatLitteral(QByteArray );
    bool isNumericLitteral(QByteArray );
    bool isBoolLitteral(QByteArray );
    bool isAccessSeparator(QByteArray );
    bool isSeparator(QByteArray );
    bool isAssignmentOpererator(QByteArray );
    bool isOperationOperator(QByteArray );
    bool isComparisonOperator(QByteArray );

private:
    QList<TokenizeItem> availableTokens;

    QRegularExpression regexpPureNumber;
    QRegularExpression regexpFloat;
    QRegularExpression regexpPureString;
    QRegularExpression regexpStartsWithNumber;
    QRegularExpression regexpIdentifierAcceptedCharacters;

private:
    //Order is:
    //Lines<Tokens<Token>>
    QList<QList<Token>> tokenizedLines;
    QStack<TokenType> separatorPriority;
};

#endif // LEXER_HPP
