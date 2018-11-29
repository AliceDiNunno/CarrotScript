#ifndef SCRIPTMEMORYBINDING_HPP
#define SCRIPTMEMORYBINDING_HPP

struct ParsingTreeValue;
struct ParsingTreeAccessor;
class ScriptMemoryBinding
{
public:
    virtual ~ScriptMemoryBinding();
    virtual ParsingTreeValue *readValue(ParsingTreeAccessor *) = 0;
    virtual void setValue(ParsingTreeAccessor *name, ParsingTreeValue *) = 0;
};

#endif // SCRIPTMEMORYBINDING_HPP
