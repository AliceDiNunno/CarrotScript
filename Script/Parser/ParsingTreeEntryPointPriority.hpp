#ifndef PARSINGTREEENTRYPOINTPRIORITY_HPP
#define PARSINGTREEENTRYPOINTPRIORITY_HPP

enum ParsingTreeEntryPointPriority
{
    PTEPP_Unknown = -1,

    PTEPP_FunctionCall = 0,
    PTEPP_Assignation = 1,
    PTEPP_Keyword = 2,
};

#endif // PARSINGTREEENTRYPOINTPRIORITY_HPP
