#ifndef PARSINGTREEFUNCTIONCALL_HPP
#define PARSINGTREEFUNCTIONCALL_HPP

#include <QList>
#include "ParsingTreeEntryPoint.hpp"

struct ParsingTreeAccessor;
struct ParsingTreeFunctionCall: public ParsingTreeEntryPoint
{
    ParsingTreeFunctionCall();
    ~ParsingTreeFunctionCall();

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory);

    QList<ParsingTreeValue *> arguments;
    ParsingTreeAccessor *source;
};

#endif // PARSINGTREEFUNCTIONCALL_HPP
