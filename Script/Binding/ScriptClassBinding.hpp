#ifndef SCRIPTCLASSBINDING_HPP
#define SCRIPTCLASSBINDING_HPP

#include <QList>
#include <QByteArray>

#include "ScriptMemoryBinding.hpp"

struct ParsingTreeValue;
struct ParsingTreeAccessor;
struct ParsingTreeFunctionDeclaration;
class ScriptClassBinding: public ScriptMemoryBinding
{
public:
    virtual QList<ParsingTreeFunctionDeclaration *> functions() = 0;
    virtual ParsingTreeFunctionDeclaration *function(QList<QByteArray> arguments) = 0;

    virtual ParsingTreeValue *readValue(ParsingTreeAccessor *) = 0;
    virtual void setValue(ParsingTreeAccessor *name, ParsingTreeValue *) = 0;
};

#endif // SCRIPTCLASSBINDING_HPP
