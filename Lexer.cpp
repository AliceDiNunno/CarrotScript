#include <QStringList>
#include <QRegularExpression>
#include "Lexer.hpp"

Lexer::Lexer()
{
    regexpPureNumber = QRegularExpression("^([0-9]*)$");
    regexpPureString = QRegularExpression("^\"(.*?)\"$");
    regexpStartsWithNumber = QRegularExpression("^([0-9].*)$");
    regexpIdentifierAcceptedCharacters = QRegularExpression("^[a-zA-Z0-9_]*$");
}

bool Lexer::isIdentifier(QString aElement)
{
    QRegularExpressionMatch acceptedCharacterMatch = regexpIdentifierAcceptedCharacters.match(aElement);
    QRegularExpressionMatch startsWithNumber = regexpStartsWithNumber.match(aElement);
    return (acceptedCharacterMatch.hasMatch() && !startsWithNumber.hasMatch());
}

bool Lexer::isKeyword(QString aElement)
{
    QStringList keywords = {"if", "else", "true", "false", "import", "require", "set"};
    return keywords.contains(aElement);
}

bool Lexer::isSeparator(QString aElement)
{
    QStringList separator = {"(", ")", "{", "}", "[", "]", ",", "."};
    return separator.contains(aElement);
}

bool Lexer::isOperationOperator(QString aElement)
{
    QStringList operators = {"+", "-", "/", "*"};
    return operators.contains(aElement);
}

bool Lexer::isAssignmentOpererator(QString aElement)
{
    return aElement == "=";
}

bool Lexer::isComparisonOperator(QString aElement)
{
    QStringList operators = {"==", "!=", "<=", ">=", "<", ">"};
    return operators.contains(aElement);
}

bool Lexer::isOperator(QString aElement)
{
    return isComparisonOperator(aElement) || isAssignmentOpererator(aElement) || isOperationOperator(aElement);
}

bool Lexer::isLitteral(QString aElement)
{
    //TODO: float
    //TODO: char

    QRegularExpressionMatch matchString = regexpPureString.match(aElement);
    QRegularExpressionMatch matchInt = regexpPureNumber.match(aElement);

    return matchString.hasMatch() || matchInt.hasMatch();
}

bool Lexer::isComment(QString aElement)
{
    return false;
}
