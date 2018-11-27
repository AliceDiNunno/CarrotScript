#ifndef TOKENIZEITEM_HPP
#define TOKENIZEITEM_HPP

#include <QByteArray>
#include "Token.hpp"

class Lexer;
struct TokenizeItem
{
    Token tokenIfMatch;
    bool (Lexer::*check)(QByteArray );
};

#endif // TOKENIZEITEM_HPP
