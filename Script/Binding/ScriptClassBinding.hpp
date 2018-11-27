#ifndef SCRIPTCLASSBINDING_HPP
#define SCRIPTCLASSBINDING_HPP

#include <QList>
#include <QByteArray>

#include "../Memory/ParsingTreeAccessor.hpp"
#include "../Parser/ParsingTreeFunctionDeclaration.hpp"
#include "../Types/ParsingTreeValue.hpp"
#include "ScriptMemoryBinding.hpp"

class ScriptClassBinding: public ScriptMemoryBinding
{
public:
    virtual QList<ParsingTreeFunctionDeclaration *> functions() = 0;
    virtual ParsingTreeFunctionDeclaration *function(QList<QByteArray> arguments) = 0;

    virtual ParsingTreeValue *readValue(ParsingTreeAccessor *) = 0;
    virtual void setValue(ParsingTreeAccessor *name, ParsingTreeValue *) = 0;
};

#endif // SCRIPTCLASSBINDING_HPP
