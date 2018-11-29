#include "ParsingTreeCondition.hpp"
#include "../Operations/ParsingTreeComparison.hpp"

ParsingTreeCondition::ParsingTreeCondition()
{
    debugName = "ParsingTreeCondition";
}

ParsingTreeValue *ParsingTreeCondition::execute(MemoryManagement *pMemory)
{
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
                executeSuccess(pMemory);
            }
            else
            {
                executeFallback(pMemory);
            }
        }
        else if (type == PTKT_While)
        {
            while(run())
            {
                executeSuccess(pMemory);
            }
        }
        else
        {
            //Err
        }
    }
    else
    {
        //Err
    }
    executeNext(pMemory);
    return nullptr;
}
