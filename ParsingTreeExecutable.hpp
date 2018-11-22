#ifndef PARSINGTREEEXECUTABLE_HPP
#define PARSINGTREEEXECUTABLE_HPP

#include <QtDebug>

class MemoryManagement;
struct ParsingTreeValue;

static int myline = 0;

struct ParsingTreeExecutable
{
    ParsingTreeExecutable()
    {
        success = nullptr;
        fallback = nullptr;
        next = nullptr;
    }

    virtual ~ParsingTreeExecutable()
    {
    }

    virtual ParsingTreeValue *execute(MemoryManagement *) = 0;

    ParsingTreeValue *executeNext(MemoryManagement *apMem)
    {
        if (next)
        {
            myline++;
            qDebug() << "NEXT: " << line;
            return next->execute(apMem);
        }
        return nullptr;
    }

    ParsingTreeValue *executeFallback(MemoryManagement *apMem)
    {
        if (fallback)
        {
            myline++;
            qDebug() << "FAIL: " << line;
            return fallback->execute(apMem);
        }
        return nullptr;
    }

    ParsingTreeValue *executeSuccess(MemoryManagement *apMem)
    {
        if (success)
        {
            myline++;
            qDebug() << "SUCCESS: " << line;
            return success->execute(apMem);
        }
        return nullptr;
    }

    ParsingTreeExecutable *success;
    ParsingTreeExecutable *fallback;
    ParsingTreeExecutable *next;

    int lineNumber;
    QString line;
};

#endif // PARSINGTREEEXECUTABLE_HPP
