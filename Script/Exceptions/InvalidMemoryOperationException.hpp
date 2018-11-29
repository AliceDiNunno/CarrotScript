#ifndef INVALIDMEMORYOPERATIONEXCEPTION_HPP
#define INVALIDMEMORYOPERATIONEXCEPTION_HPP

#include "CarrotScriptException.hpp"

class InvalidMemoryOperationException: public CarrotScriptException
{
public:
    InvalidMemoryOperationException(QString detail,
                                    QString fileName,
                                    QString line,
                                    int lineNumber,
                                    int colNumber);
};

#endif // INVALIDMEMORYOPERATIONEXCEPTION_HPP
