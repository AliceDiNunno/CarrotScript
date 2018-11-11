#ifndef DATASANATIZER_HPP
#define DATASANATIZER_HPP

#include <QByteArray>
#include <QList>

struct ColumnTranslator
{
    int columnNumber;
    int originalColumnNumber;
};

struct LineTranslator
{
    int lineNumber;
    int originalLineNumber;
    QMap<int, ColumnTranslator> columns;
};

class DataSanatizer
{
public:
    DataSanatizer();

    QByteArray sanitize(QByteArray);
    int getOriginalLineNumber(int aLineNumber);
    int getOriginalColumnNumber(int aLineNumber, int aColumn);

private:
    bool isSpace(char );
    bool isNextLine(char );
    bool isSpecialChar(char );
    char getNextCharacter(QByteArray data, int currentPosition);

private:
    QList<LineTranslator> _line;
};

#endif // DATASANATIZER_HPP
