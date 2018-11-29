#ifndef INVALIDOPERATIONEXCEPTION_HPP
#define INVALIDOPERATIONEXCEPTION_HPP

#include "CarrotScriptException.hpp"

class InvalidOperationException: public CarrotScriptException
{
public:
    InvalidOperationException(QString detail,
                              QString fileName,
                              QString line,
                              int lineNumber,
                              int colNumber);
};

#endif // INVALIDOPERATIONEXCEPTION_HPP
