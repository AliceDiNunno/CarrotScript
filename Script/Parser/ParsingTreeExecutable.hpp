#ifndef PARSINGTREEEXECUTABLE_HPP
#define PARSINGTREEEXECUTABLE_HPP

#include <QString>

class MemoryManagement;
struct ParsingTreeValue;
struct ParsingTreeExecutable
{
    ParsingTreeExecutable();
    virtual ~ParsingTreeExecutable();

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
    QString debugName;
};

#endif // PARSINGTREEEXECUTABLE_HPP
