#ifndef PARSINGTREEEXECUTABLE_HPP
#define PARSINGTREEEXECUTABLE_HPP

#include <QtDebug>

class MemoryManagement;
struct ParsingTreeValue;

static int myline = 0;

struct ParsingTreeExecutable
{
    QString debugName;

    ParsingTreeExecutable()
    {
        debugName = "ParsingTreeExecutable";
        success = nullptr;
        fallback = nullptr;
        next = nullptr;
    }

    virtual ~ParsingTreeExecutable()
    {
    }

    virtual ParsingTreeValue *execute(MemoryManagement *) = 0;

    void checkScope(MemoryManagement *apMem);

    ParsingTreeValue *executeNext(MemoryManagement *apMem);
    ParsingTreeValue *executeFallback(MemoryManagement *apMem);
    ParsingTreeValue *executeSuccess(MemoryManagement *apMem);

    ParsingTreeExecutable *success;
    ParsingTreeExecutable *fallback;
    ParsingTreeExecutable *next;

    int lineNumber;
    QString line;

    int scopeChange = 0;
    bool didEnter = false;
    int scopeCheck = 0;
};

#endif // PARSINGTREEEXECUTABLE_HPP
