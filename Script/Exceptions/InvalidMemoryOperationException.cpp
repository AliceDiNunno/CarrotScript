#include "InvalidMemoryOperationException.hpp"

InvalidMemoryOperationException::InvalidMemoryOperationException(QString detail,
                                                                 QString fileName,
                                                                 QString line,
                                                                 int lineNumber,
                                                                 int colNumber):
                                            CarrotScriptException ("InvalidMemoryOperation",
                                                                   detail,
                                                                   fileName,
                                                                   line,
                                                                   lineNumber,
                                                                   colNumber)
{

}
