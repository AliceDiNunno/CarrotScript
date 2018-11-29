#include "InvalidOperationException.hpp"

InvalidOperationException::InvalidOperationException(QString detail,
                                                     QString fileName,
                                                     QString line,
                                                     int lineNumber,
                                                     int colNumber):
                                CarrotScriptException ("InvalidOperation",
                                                       detail,
                                                       fileName,
                                                       line,
                                                       lineNumber,
                                                       colNumber)
{

}
