#include "InterpreterErrorException.hpp"

InterpreterErrorException::InterpreterErrorException(QString detail,
                                             QString fileName,
                                             QString line,
                                             int lineNumber,
                                             int colNumber):
                        CarrotScriptException ("InterpreterError",
                                               detail,
                                               fileName,
                                               line,
                                               lineNumber,
                                               colNumber)
{

}
