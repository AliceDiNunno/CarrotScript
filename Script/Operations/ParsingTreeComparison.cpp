#include "ParsingTreeComparison.hpp"
#include "../Exceptions/InvalidComparisonException.hpp"

ParsingTreeComparison::ParsingTreeComparison()
{
    successOnFailure = false;
    debugName = "ParsingTreeComparison";
}

ParsingTreeValue *ParsingTreeComparison::execute(MemoryManagement *pMemory)
{
    if (left == nullptr || right == nullptr)
    {
        if (left == nullptr)
            throw InvalidComparisonException("Left member is null", "", line, lineNumber, -1);
        else
            throw InvalidComparisonException("Right member is null", "", line, lineNumber, -1);
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
        throw InvalidComparisonException("Invalid comparison operator", "", line, lineNumber, -1);
    }

    if (successOnFailure)
        result = !result;

    ParsingTreeBoolean *ptb = new ParsingTreeBoolean();
    ptb->value = result;

    return ptb;
}
