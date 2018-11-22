#ifndef PARSINGTREEFUNCTIONCALL_HPP
#define PARSINGTREEFUNCTIONCALL_HPP

#include <QList>
#include "ParsingTreeAccessor.hpp"
#include "ParsingTreeEntryPoint.hpp"
#include "ParsingTreeValue.hpp"
#include "MemoryManagement.hpp"

#include <QDebug>

struct ParsingTreeFunctionCall: public ParsingTreeEntryPoint
{
    QList<ParsingTreeValue *> arguments;
    ParsingTreeAccessor *source;

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory) override
    {
        ParsingTreeValue *pResult = pMemory->callFunction(source, arguments);
        executeNext(pMemory);

        return pResult;
    }
};

#endif // PARSINGTREEFUNCTIONCALL_HPP
