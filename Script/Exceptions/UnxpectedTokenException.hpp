#ifndef UNXPECTEDTOKENEXCEPTION_HPP
#define UNXPECTEDTOKENEXCEPTION_HPP

#include "CarrotScriptException.hpp"

class UnxpectedTokenException: public CarrotScriptException
{
public:
    UnxpectedTokenException(QString detail,
                            QString fileName,
                            QString line,
                            int lineNumber,
                            int colNumber);
};

#endif // UNXPECTEDTOKENEXCEPTION_HPP
