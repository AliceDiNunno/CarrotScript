#ifndef FILEREADIN_HPP
#define FILEREADIN_HPP

#include <QString>

class ByteReader
{
public:
    ByteReader(QByteArray data);

    QChar readNextToken();
    int getCurrentLine();
    int getCurrentCol();

private:
    int _line;
    int _col;
    bool _wasCarriageReturn;
    QByteArray _data;
};

#endif // FILEREADIN_HPP
