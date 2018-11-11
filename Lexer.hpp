#ifndef LEXER_HPP
#define LEXER_HPP

#include <QString>
#include <QRegularExpression>

enum Token
{
    T_Identifier,
    T_Keyword,
    T_Separator,
    T_Operation,
    T_Assignement,
    T_Comparison,
    T_FloatLitteral,
    T_NumericLitteral,
    T_StringLitteral
};

class Lexer;
struct TokenizeItem
{
    Token tokenIfMatch;
    bool (Lexer::*check)(QByteArray );

};

class UnknownTokenException: public std::exception
{

};

class Lexer
{
public:
    Lexer();

    void parseFile(QByteArray );
    Token tokenize(QByteArray );
    QList<QList<QPair<Token, QByteArray>>> getAllTokens();

private:
    bool isIdentifier(QByteArray );
    bool isKeyword(QByteArray );
    bool isOperationOperator(QByteArray );
    bool isAssignmentOpererator(QByteArray );
    bool isComparisonOperator(QByteArray );
    bool isOperator(QByteArray );
    bool isSeparator(QByteArray );
    bool isStringLitteral(QByteArray );
    bool isIntegerLitteral(QByteArray );
    bool isFloatLitteral(QByteArray );

private:
    QList<TokenizeItem> availableTokens;

    QRegularExpression regexpPureNumber;
    QRegularExpression regexpPureString;
    QRegularExpression regexpStartsWithNumber;
    QRegularExpression regexpIdentifierAcceptedCharacters;

private:
    //Order is:
    //Lines<Tokens<TokenType, Data>>
    QList<QList<QPair<Token, QByteArray>>> tokenizedLines;
};

#endif // LEXER_HPP
