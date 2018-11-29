#ifndef UNKNOWNTOKENEXCEPTION_HPP
#define UNKNOWNTOKENEXCEPTION_HPP

#include "CarrotScriptException.hpp"

class UnknownTokenException: public CarrotScriptException
{
public:
    UnknownTokenException(QString detail,
                          QString fileName,
                          QString line,
                          int lineNumber,
                          int colNumber);
};

#endif // UNKNOWNTOKENEXCEPTION_HPP
