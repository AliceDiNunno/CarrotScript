#include "UnxpectedTokenException.hpp"

UnxpectedTokenException::UnxpectedTokenException(QString detail,
                                                 QString fileName,
                                                 QString line,
                                                 int lineNumber,
                                                 int colNumber):
                            CarrotScriptException ("UnexpectedToken",
                                                   detail,
                                                   fileName,
                                                   line,
                                                   lineNumber,
                                                   colNumber){

}
