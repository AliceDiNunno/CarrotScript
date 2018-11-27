#ifndef PARSINGTREEENTRYPOINT_HPP
#define PARSINGTREEENTRYPOINT_HPP

#include "../Types/ParsingTreeValue.hpp"

struct ParsingTreeEntryPoint: ParsingTreeValue
{
public:
    virtual ~ParsingTreeEntryPoint() {}

    ParsingTreeEntryPoint()
    {
        debugName = "ParsingTreeEntryPoint";
    }
};


#endif // PARSINGTREEENTRYPOINT_HPP
