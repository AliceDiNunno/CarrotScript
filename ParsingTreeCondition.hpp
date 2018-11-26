#ifndef PARSINGTREECONDITION_HPP
#define PARSINGTREECONDITION_HPP

#include "ParsingTreeKeyword.hpp"
#include "ParsingTreeComparison.hpp"
#include "ParsingTreeBoolean.hpp"

struct ParsingTreeCondition: public ParsingTreeKeyword
{
    ParsingTreeComparison *condition = nullptr;

    ParsingTreeCondition()
    {
        debugName = "ParsingTreeCondition";
    }

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory)
    {
        //qDebug() << "exec: " << line << lineNumber;
        if (condition)
        {
            auto run = [this, pMemory]()
            {
                ParsingTreeBoolean *bol = dynamic_cast<ParsingTreeBoolean *>(condition->execute(pMemory));
                if (!bol)
                {
                    return false; //Throw err
                }
                return bol->value;
            };

            if (type == PTKT_If)
            {
                if (run())
                {
                   // qDebug() << "IF SUCCESS";
                    executeSuccess(pMemory);
                }
                else
                {
                    //qDebug() << "IF FAIL";
                    executeFallback(pMemory);
                }
            }
            else if (type == PTKT_While)
            {
                while(run())
                {
                   // qDebug() << "IN LOOP";
                    executeSuccess(pMemory);
                }
            }
            else
            {
                //Err
              //  qDebug() << "NO CAN DO";
            }
        }
        else
        {
          //  qDebug() << "UNKNOWN CONDITION";
        }
        //qDebug() << "GO NEXT";
        executeNext(pMemory);

        return nullptr;
    }
};

#endif // PARSINGTREECONDITION_HPP
