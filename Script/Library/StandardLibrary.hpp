#ifndef STANDARDLIBRARY_HPP
#define STANDARDLIBRARY_HPP

#include "../Binding/ScriptClassBinding.hpp"

class StandardLibrary: public ScriptClassBinding
{
public:
    StandardLibrary(MemoryManagement *apMemoryManagement);
    virtual QString className();
    virtual QMap<QString, std::function<ParsingTreeValue *(const QList<QVariant> &)> > functions();
};

#endif // STANDARDLIBRARY_HPP
