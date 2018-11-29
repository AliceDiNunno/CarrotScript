#ifndef SCRIPTCLASSBINDING_HPP
#define SCRIPTCLASSBINDING_HPP

#include <QList>
#include <QByteArray>

#include "ScriptMemoryBinding.hpp"

struct ParsingTreeValue;
struct ParsingTreeAccessor;
struct ParsingTreeFunctionDeclaration;
class MemoryManagement;
class ScriptClassBinding: public ScriptMemoryBinding
{
public:
    ScriptClassBinding(MemoryManagement *apMemoryManagement);
    virtual QString className() = 0;

    virtual QMap<QString, std::function<ParsingTreeValue *(const QList<QVariant> &)>> functions() = 0;

protected:
    MemoryManagement *_pMemory;
};

#endif // SCRIPTCLASSBINDING_HPP
