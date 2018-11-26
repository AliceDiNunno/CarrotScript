#ifndef PARSINGTREEOPERATION_HPP
#define PARSINGTREEOPERATION_HPP

#include "ParsingTreeValue.hpp"
#include "ParsingTreeOperationType.hpp"
#include "MemoryManagement.hpp"
#include "ParsingTreeInteger.hpp"
#include "ParsingTreeFloat.hpp"

struct ParsingTreeOperation: public ParsingTreeValue
{
    ParsingTreeValue *left;
    ParsingTreeOperationType type;
    ParsingTreeValue *right;

    ParsingTreeOperation()
    {
        debugName = "ParsingTreeOperation";
    }


    ParsingTreeValue *makeOperation(ParsingTreeValue *left, ParsingTreeValue *right)
    {
        switch (type)
        {
        case PTOT_Add:
            return left->add(right);
        case PTOT_Remove:
            return left->remove(right);
        case PTOT_Divide:
            return left->divide(right);
        case PTOT_Multiply:
            return left->multiply(right);
        default:
            return nullptr; //todo err
        }
    }

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory)
    {
        ParsingTreeValue *lExecute = nullptr;
        ParsingTreeValue *rExecute = nullptr;

        if (left != nullptr)
            lExecute = left->execute(pMemory);
        if (right != nullptr)
            rExecute = right->execute(pMemory);

        if (lExecute == nullptr)
        {
            return rExecute;
        }
        else if (rExecute == nullptr)
        {
            return lExecute;
        }
        else if (lExecute == nullptr && rExecute == nullptr)
        {
            return nullptr; //err
        }

        return makeOperation(lExecute, rExecute);
    }
};

#endif // PARSINGTREEOPERATION_HPP
