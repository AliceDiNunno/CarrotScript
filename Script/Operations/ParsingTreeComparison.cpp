#include "ParsingTreeComparison.hpp"

ParsingTreeComparison::ParsingTreeComparison()
{
    successOnFailure = false;
    debugName = "ParsingTreeComparison";
}

ParsingTreeValue *ParsingTreeComparison::execute(MemoryManagement *pMemory)
{
    if (left == nullptr || right == nullptr)
    {
        return nullptr; //err
    }
    QVariant l = MemoryManagement::translateValue(left->execute(pMemory));
    QVariant r = MemoryManagement::translateValue(right->execute(pMemory));

    bool result = false;

    switch (type)
    {
    case PTVCT_And:
        result = l.toBool() && r.toBool();
        break;
    case PTVCT_Or:
        result = l.toBool() || r.toBool();
        break;
    case PTVCT_BiggerOrEqualsThan:
        result = (l >= r);
        break;
    case PTVCT_BiggerThan:
        result = (l > r);
        break;
    case PTVCT_SmallerOrEqualsThan:
        result = (l <= r);
        break;
    case PTVCT_SmallerThan:
        result = (l < r);
        break;
    case PTVCT_Equals:
        result = (l == r);
        break;
    case PTVCT_NotEquals:
        result = (l != r);
        break;
    default:
        //ERR
        break;
    }

    if (successOnFailure)
        result = !result;

    ParsingTreeBoolean *ptb = new ParsingTreeBoolean();
    ptb->value = result;

    return ptb;
}
