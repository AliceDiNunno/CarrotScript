#ifndef CARROTSCRIPTEXCEPTION_HPP
#define CARROTSCRIPTEXCEPTION_HPP

#include <stdexcept>
#include <QString>
#include <QtDebug>
#include <QException>

class CarrotScriptException: public std::exception
{
public:
    CarrotScriptException(QString errorName,
                          QString detail,
                          QString fileName,
                          QString line,
                          int lineNumber,
                          int colNumber);
    const QString exceptionDetail() const;
    virtual const char* what() const noexcept;

private:
    QString _errorName;
    QString _detail;
    QString _fileName;
    QString _line;
    int _lineNumber;
    int _colNumber;
};

#endif // CARROTSCRIPTEXCEPTION_HPP
