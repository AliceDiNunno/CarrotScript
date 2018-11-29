#ifndef INTERPRETERERROREXCEPTION_HPP
#define INTERPRETERERROREXCEPTION_HPP

#include "CarrotScriptException.hpp"

class InterpreterErrorException: public CarrotScriptException
{
public:
    InterpreterErrorException(QString detail,
                              QString fileName,
                              QString line,
                              int lineNumber,
                              int colNumber);
};

#endif // INTERPRETERERROREXCEPTION_HPP
