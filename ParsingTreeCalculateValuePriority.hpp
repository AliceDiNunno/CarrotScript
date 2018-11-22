#ifndef PARSINGTREECALCULATEVALUEPRIORITY_HPP
#define PARSINGTREECALCULATEVALUEPRIORITY_HPP

enum ParsingTreeCalculateValuePriority
{
    PTCVP_Unsupported = -1,
    PTCVP_Or = 1,
    PTCVP_And = 2,
    PTCVP_Comparison = 3,
    PTCVP_PlusMinus = 4,
    PTCVP_MultiplyDivide = 5,
    PTCVP_Parenthesis = 6
};

#endif // PARSINGTREECALCULATEVALUEPRIORITY_HPP
