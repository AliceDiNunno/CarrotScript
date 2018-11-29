#include "ParsingTreeOperation.hpp"
#include "../Exceptions/InvalidOperationException.hpp"

ParsingTreeOperation::ParsingTreeOperation()
{
    debugName = "ParsingTreeOperation";
}

ParsingTreeValue *ParsingTreeOperation::makeOperation(ParsingTreeValue *left, ParsingTreeValue *right)
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

ParsingTreeValue *ParsingTreeOperation::execute(MemoryManagement *pMemory)
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
        throw InvalidOperationException("Empty Operation", "", "", -1, -1);
    }

    return makeOperation(lExecute, rExecute);
}
