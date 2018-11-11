#include "DataSanatizer.hpp"
#include <QtDebug>

DataSanatizer::DataSanatizer()
{

}

QByteArray DataSanatizer::sanitize(QByteArray data)
{
    QByteArray sanitizedData;

    data = data.replace("\r\n", "\n"); //Removing windows-style carriage return (They really can't do anything like anyone else)

    QByteArray currentLine = QByteArray();
    bool wasSpace = false;
    bool isEmpty = true;
    char lastCharacter = 0;
    bool isComment = false;
    bool ignoreRestOfLine = false;
    bool isInQuote = false;
    for (int i = 0; i < data.count(); i++)
    {
        char c = data.at(i);

        if (c == '"')
            isInQuote = !isInQuote;

        if (ignoreRestOfLine && !isNextLine(c))
            continue;

        if (isNextLine(c))
        {
            if (isInQuote)
            {
                currentLine.append(" "); //TODO: ? not sure if adding a space on new multine lines is ok or not, to check ?
                continue;
            }
            if (!currentLine.isEmpty())
            {
                if (isSpace(currentLine.at(currentLine.count() - 1)))
                    currentLine.remove(currentLine.count() - 1, 1);

                sanitizedData.append(c + currentLine);
                currentLine = QByteArray();
            }
            wasSpace = false;
            isEmpty = true;
            isComment = false;
            lastCharacter = 0;
            ignoreRestOfLine = false;
            isInQuote = false;
            continue;
        }

        if (lastCharacter == 0 && isSpace(c))
            continue;

        if (wasSpace && isSpace(c))
            continue;

        wasSpace = isSpace(c);
        if (isSpace(c))
            c = ' '; //replacing potential \t by space

        if(c == '/' && getNextCharacter(data, i) == '/' && !isInQuote)
        {
            ignoreRestOfLine = true;
            continue;
        }

        lastCharacter = c;
        currentLine.append(c);

        if (!isInQuote)
        {
            if ((QChar(c).isLetterOrNumber() && isSpecialChar(getNextCharacter(data, i))) ||
               (QChar(getNextCharacter(data, i)).isLetterOrNumber() && isSpecialChar(c)))
            {
                currentLine.append(' ');
            }
        }
    }

    if (isInQuote)
    {
        qDebug() << "ERROR: UNTERMINATED QUOTE";
    }

    return sanitizedData;
}

bool DataSanatizer::isSpecialChar(char c)
{
    return c == '+' ||
           c == '-' ||
           c == '/' ||
           c == '*' ||
           c == '=' ||
           c == '(' ||
           c == ')';
}

bool DataSanatizer::isSpace(char c)
{
    return c == '\t' || c == ' ';
}

bool DataSanatizer::isNextLine(char c)
{
    return c == '\n';
}

char DataSanatizer::getNextCharacter(QByteArray data, int currentPosition)
{
    if (currentPosition + 1 >= data.count())
        return 0;
    return data.at(currentPosition + 1);
}
