#ifndef PARSINGTREEFUNCTIONCALL_HPP
#define PARSINGTREEFUNCTIONCALL_HPP

#include <QList>
#include "../Memory/ParsingTreeAccessor.hpp"
#include "ParsingTreeEntryPoint.hpp"
#include "../Types/ParsingTreeValue.hpp"
#include "../Memory/MemoryManagement.hpp"

#include <QDebug>

struct ParsingTreeFunctionCall: public ParsingTreeEntryPoint
{
    QList<ParsingTreeValue *> arguments;
    ParsingTreeAccessor *source;

    ParsingTreeFunctionCall()
    {
        debugName = "ParsingTreeFunctionCall";
    }

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory) override
    {
        ParsingTreeValue *pResult = pMemory->callFunction(source, arguments);
        executeNext(pMemory);

        return pResult;
    }
};

#endif // PARSINGTREEFUNCTIONCALL_HPP
