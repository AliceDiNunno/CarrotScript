#include "CarrotScriptException.hpp"

CarrotScriptException::CarrotScriptException(QString errorName,
                                             QString detail,
                                             QString fileName,
                                             QString line,
                                             int lineNumber,
                                             int colNumber):

                                             _errorName(errorName),
                                             _detail(detail),
                                             _fileName(fileName),
                                             _line(line),
                                             _lineNumber(lineNumber),
                                             _colNumber(colNumber)
{

}

const QString CarrotScriptException::exceptionDetail() const
{
    return QString("CarrotScript: %1Exception: %2\n%3\nin File: %4 %5:%6").arg(_errorName).arg(_detail)
            .arg(_line)
            .arg(_fileName).arg(_lineNumber).arg(_colNumber);
}

const char* CarrotScriptException::what() const noexcept
{
    QString line = exceptionDetail();
    return line.toStdString().c_str();
}
