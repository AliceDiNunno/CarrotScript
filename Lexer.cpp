#include <QStringList>
#include <QRegularExpression>
#include "Lexer.hpp"
#include <QDebug>

QString tts(Token t)
{
    if (t == T_Identifier)
    {
        return "T_Identifier";
    }
    if (t == T_Keyword)
    {
        return "T_Keyword";
    }
    if (t == T_Separator)
    {
        return "T_Separator";
    }
    if (t == T_Operation)
    {
        return "T_Operation";
    }
    if (t == T_Assignement)
    {
        return "T_Assignement";
    }
    if (t == T_FloatLitteral)
    {
        return "T_FloatLitteral";
    }
    if (t == T_NumericLitteral)
    {
        return "T_NumericLitteral";
    }
    if (t == T_StringLitteral)
    {
        return "T_StringLitteral";
    }
    if (t == T_Comparison)
    {
        return "T_Comparison";
    }
    return "none";
}

Lexer::Lexer()
{
    regexpPureNumber = QRegularExpression("^([0-9]*)$");
    regexpPureString = QRegularExpression("^\"(.*?)\"$");
    regexpStartsWithNumber = QRegularExpression("^([0-9].*)$");
    regexpIdentifierAcceptedCharacters = QRegularExpression("^[a-zA-Z0-9_]*$");
    availableTokens =
    {
        { T_Keyword, &Lexer::isKeyword },
        { T_Identifier, &Lexer::isIdentifier },
        { T_StringLitteral, &Lexer::isStringLitteral },
        { T_NumericLitteral, &Lexer::isIntegerLitteral },
        { T_Separator, &Lexer::isSeparator },
        { T_Assignement, &Lexer::isAssignmentOpererator },
        { T_Operation, &Lexer::isOperationOperator },
        { T_Comparison, &Lexer::isComparisonOperator },
    };
}

bool Lexer::isKeyword(QByteArray aElement)
{
    QStringList keywords = {"if", "else", "true", "false", "import", "require", "set", "end", "add", "message", "while"};
    return keywords.contains(aElement);
}

bool Lexer::isIdentifier(QByteArray aElement)
{
    QRegularExpressionMatch acceptedCharacterMatch = regexpIdentifierAcceptedCharacters.match(aElement);
    QRegularExpressionMatch startsWithNumber = regexpStartsWithNumber.match(aElement);
    return (acceptedCharacterMatch.hasMatch() && !startsWithNumber.hasMatch());
}

bool Lexer::isSeparator(QByteArray aElement)
{
    QStringList separator = {"(", ")", "{", "}", "[", "]", ",", "."};
    return separator.contains(aElement);
}

bool Lexer::isOperationOperator(QByteArray aElement)
{
    QStringList operators = {"+", "-", "/", "*"};
    return operators.contains(aElement);
}

bool Lexer::isAssignmentOpererator(QByteArray aElement)
{
    QStringList operators = {"-=", "+=", "++", "--", "*=", "/=", "="};
    return operators.contains(aElement);
}

bool Lexer::isComparisonOperator(QByteArray aElement)
{
    QStringList operators = {"==", "!=", "<=", ">=", "<", ">"};
    return operators.contains(aElement);
}

bool Lexer::isOperator(QByteArray aElement)
{
    return isComparisonOperator(aElement) || isAssignmentOpererator(aElement) || isOperationOperator(aElement);
}

bool Lexer::isStringLitteral(QByteArray aElement)
{
    QRegularExpressionMatch matchString = regexpPureString.match(aElement);
    return matchString.hasMatch();
}

bool Lexer::isIntegerLitteral(QByteArray aElement)
{
    QRegularExpressionMatch matchNumber = regexpPureNumber.match(aElement);
    return matchNumber.hasMatch();
}

void Lexer::parseFile(QByteArray content)
{
    QList<QByteArray> lines = content.split('\n');

    for (int iLine = 0; iLine < lines.count(); iLine++)
    {
        QByteArray currentLine = lines.at(iLine);
        QList<QPair<Token, QByteArray>> lineTokens;

        QByteArray current;
        bool isInQuote = false;
        for (int iCharacter = 0; iCharacter < currentLine.count(); iCharacter++)
        {
            char c = currentLine.at(iCharacter);

            if (c == '"')
            {
                isInQuote = !isInQuote;
                current.append(c);
                if (!isInQuote)
                {
                    QPair<Token, QByteArray> newToken;
                    newToken.first = tokenize(current);
                    newToken.second = current;
                    lineTokens.append(newToken);
                    current = QByteArray();
                }
                continue;
            }

            if ((!isInQuote && c != ' ') || isInQuote)
                current.append(c);
            if (!isInQuote && (c == ' ' || iCharacter + 1 >= currentLine.count()))
            {
                QPair<Token, QByteArray> newToken;
                newToken.first = tokenize(current);
                newToken.second = current;
                lineTokens.append(newToken);
                current = QByteArray();
            }
        }
        tokenizedLines.append(lineTokens);
    }
}

Token Lexer::tokenize(QByteArray currentToken)
{
    for (int iAvailableTokens = 0; iAvailableTokens < availableTokens.count(); iAvailableTokens++)
    {
        TokenizeItem fTokenize = availableTokens.at(iAvailableTokens);
        if((this->*(fTokenize.check))(currentToken))
        {
            return fTokenize.tokenIfMatch;
        }
    }
    throw UnknownTokenException();
}

QList<QList<QPair<Token, QByteArray>>> Lexer::getAllTokens()
{
    return tokenizedLines;
}
