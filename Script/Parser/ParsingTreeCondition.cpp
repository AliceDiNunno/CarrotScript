#include "ParsingTreeCondition.hpp"
#include "../Operations/ParsingTreeComparison.hpp"
#include "../Exceptions/UnknownTokenException.hpp"
#include "../Exceptions/InvalidComparisonException.hpp"

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
                throw InvalidComparisonException("Condition does not return a 'bool' value", "", "", -1, -1);
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
            throw UnknownTokenException("Unknown condition type", "", "", -1, -1);
        }
    }
    else
    {    
        throw InvalidComparisonException("Condition is null", "", "", -1, -1);
    }
    executeNext(pMemory);
    return nullptr;
}
