#ifndef SCRIPTMEMORYBINDING_HPP
#define SCRIPTMEMORYBINDING_HPP

#include "../Types/ParsingTreeValue.hpp"
#include "../Memory/ParsingTreeAccessor.hpp"

class ScriptMemoryBinding
{
public:
    virtual ParsingTreeValue *readValue(ParsingTreeAccessor *) = 0;
    virtual void setValue(ParsingTreeAccessor *name, ParsingTreeValue *) = 0;
};

#endif // SCRIPTMEMORYBINDING_HPP
