#ifndef BADACCESSOREXCEPTION_HPP
#define BADACCESSOREXCEPTION_HPP

#include "CarrotScriptException.hpp"

class BadAccessorException: public CarrotScriptException
{
public:
    BadAccessorException(QString detail,
                         QString fileName,
                         QString line,
                         int lineNumber,
                         int colNumber);
};

#endif // BADACCESSOREXCEPTION_HPP
