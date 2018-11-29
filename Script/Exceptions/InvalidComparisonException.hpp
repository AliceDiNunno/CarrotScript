#ifndef INVALIDCOMPARISONEXCEPTION_HPP
#define INVALIDCOMPARISONEXCEPTION_HPP

#include "CarrotScriptException.hpp"

class InvalidComparisonException : public CarrotScriptException
{
public:
    InvalidComparisonException(QString detail,
                               QString fileName,
                               QString line,
                               int lineNumber,
                               int colNumber);
};

#endif // INVALIDCOMPARISONEXCEPTION_HPP
