#ifndef LEXER_HPP
#define LEXER_HPP

#include <QString>

class Lexer
{
public:
    Lexer();

    bool isIdentifier(QString );
    bool isKeyword(QString );
    bool isOperationOperator(QString );
    bool isAssignmentOpererator(QString );
    bool isComparisonOperator(QString );
    bool isOperator(QString );
    bool isSeparator(QString );
    bool isLitteral(QString );
    bool isComment(QString );

private:
    QRegularExpression regexpPureNumber;
    QRegularExpression regexpPureString;
    QRegularExpression regexpStartsWithNumber;
    QRegularExpression regexpIdentifierAcceptedCharacters;
};

#endif // LEXER_HPP
