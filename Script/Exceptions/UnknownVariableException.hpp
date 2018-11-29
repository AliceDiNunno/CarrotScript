#ifndef UNKNOWNVARIABLEEXCEPTION_HPP
#define UNKNOWNVARIABLEEXCEPTION_HPP

#include "CarrotScriptException.hpp"

class UnknownVariableException: public CarrotScriptException
{
public:
    UnknownVariableException(QString detail,
                             QString fileName,
                             QString line,
                             int lineNumber,
                             int colNumber);
};

#endif // UNKNOWNVARIABLEEXCEPTION_HPP
