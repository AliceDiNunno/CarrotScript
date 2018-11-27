#ifndef CARROTSCRIPTEXCEPTION_HPP
#define CARROTSCRIPTEXCEPTION_HPP

#include <stdexcept>

class CarrotScriptException: public std::exception
{
public:
    CarrotScriptException();
};

#endif // CARROTSCRIPTEXCEPTION_HPP
