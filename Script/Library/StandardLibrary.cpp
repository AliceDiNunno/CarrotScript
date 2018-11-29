#include "StandardLibrary.hpp"
#include "../Memory/MemoryManagement.hpp"
#include "../Types/ParsingTreeInteger.hpp"

StandardLibrary::StandardLibrary(MemoryManagement *apMemoryManagement): ScriptClassBinding(apMemoryManagement)
{

}

QString StandardLibrary::className()
{
    return "standard";
}

QMap<QString, std::function<ParsingTreeValue *(const QList<QVariant> &)> > StandardLibrary::functions()
{
    return {
        { "message", [this](const QList<QVariant> &args) -> ParsingTreeValue *
            {
                if (args.count() >= 1)
                    emit _pMemory->message(args.at(0).toString());
                return nullptr;
            }
        },
        { "double", [](const QList<QVariant> &args) -> ParsingTreeValue *
            {
                ParsingTreeInteger *pti = nullptr;
                if (args.count() >= 1)
                   pti = ParsingTreeInteger::make(args.at(0).toInt() * 2);
                return pti;
            }
        },
    };
}
