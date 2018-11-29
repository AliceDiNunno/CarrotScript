#include "UnknownTokenException.hpp"

UnknownTokenException::UnknownTokenException(QString detail,
                                             QString fileName,
                                             QString line,
                                             int lineNumber,
                                             int colNumber):
                        CarrotScriptException ("UnexpectedToken",
                                               detail,
                                               fileName,
                                               line,
                                               lineNumber,
                                               colNumber)
{
    qDebug() << "hello";
}
