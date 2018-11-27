#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <QString>
#include <QList>

#include "TokenType.hpp"

struct Token
{
    //Lexer
    TokenType type;
    QByteArray content;
    int lineNumber;
    QString lineStr;
    int column;

    //parser
    QList<Token> subTokens;
};

/*
bool tokenIsGroup(Token t)
{
    return t.subTokens.isEmpty();
}*/

#endif // TOKEN_HPP
