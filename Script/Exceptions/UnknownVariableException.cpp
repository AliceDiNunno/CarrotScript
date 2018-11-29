#include "UnknownVariableException.hpp"

UnknownVariableException::UnknownVariableException(QString detail,
                                                   QString fileName,
                                                   QString line,
                                                   int lineNumber,
                                                   int colNumber):
                              CarrotScriptException ("UnknownVariable",
                                                     detail,
                                                     fileName,
                                                     line,
                                                     lineNumber,
                                                     colNumber)
{

}
