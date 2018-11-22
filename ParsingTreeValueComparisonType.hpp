#ifndef PARSINGTREEVALUECOMPARISONTYPE_HPP
#define PARSINGTREEVALUECOMPARISONTYPE_HPP

enum ParsingTreeValueComparisonType
{
    PTVCT_Equals, // ==
    PTVCT_NotEquals, // !=
    PTVCT_BiggerThan, // >
    PTVCT_SmallerThan, // <
    PTVCT_BiggerOrEqualsThan, // >=
    PTVCT_SmallerOrEqualsThan, // <=
    PTVCT_And,
    PTVCT_Or,
    PTVCT_Unknown
};

#endif // PARSINGTREEVALUECOMPARISONTYPE_HPP
