#include "ParsingTreeExecutable.hpp"
#include "MemoryManagement.hpp"

void ParsingTreeExecutable::checkScope(MemoryManagement *apMem)
{
    if (scopeChange > 0)
    {
        didEnter = true;
        apMem->enterScope();
        scopeChange = 0;
    }
}

ParsingTreeValue *ParsingTreeExecutable::executeNext(MemoryManagement *apMem)
{
    ParsingTreeValue *ptv = nullptr;
    checkScope(apMem);
    if (next)
    {
        myline++;
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
        myline++;
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
        myline++;
        qDebug() << QString(line + " (%1)").arg(lineNumber);
        ptv = success->execute(apMem);
    }
    return ptv;
}
