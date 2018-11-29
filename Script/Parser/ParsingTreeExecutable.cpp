#include "ParsingTreeExecutable.hpp"
#include "../Memory/MemoryManagement.hpp"

ParsingTreeExecutable::ParsingTreeExecutable()
{
    debugName = "ParsingTreeExecutable";
    success = nullptr;
    fallback = nullptr;
    next = nullptr;
    lineNumber = 0;
    line = "";
    scopeChange = 0;
    didEnter = false;
    scopeCheck = 0;
}

ParsingTreeExecutable::~ParsingTreeExecutable()
{
}

void ParsingTreeExecutable::checkScope(MemoryManagement *apMem)
{
    if (scopeChange > 0)
    {
        didEnter = true;
        apMem->enterScope();
    }
}

ParsingTreeValue *ParsingTreeExecutable::executeNext(MemoryManagement *apMem)
{
    ParsingTreeValue *ptv = nullptr;
    checkScope(apMem);
    if (next)
    {
        qDebug() << QString(line + " (%1)").arg(lineNumber);
        ptv = next->execute(apMem);
    }
    return nullptr;
}

ParsingTreeValue *ParsingTreeExecutable::executeFallback(MemoryManagement *apMem)
{
    ParsingTreeValue *ptv = nullptr;
    checkScope(apMem);
    if (fallback)
    {
        qDebug() << QString(line + " (%1)").arg(lineNumber);
        ptv = fallback->execute(apMem);
    }
    return ptv;
}

ParsingTreeValue *ParsingTreeExecutable::executeSuccess(MemoryManagement *apMem)
{
    ParsingTreeValue *ptv = nullptr;
    checkScope(apMem);
    if (success)
    {
        qDebug() << QString(line + " (%1)").arg(lineNumber);
        ptv = success->execute(apMem);
    }
    return ptv;
}
