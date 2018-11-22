#ifndef PARSINGTREEACCESSOR_HPP
#define PARSINGTREEACCESSOR_HPP

#include "ParsingTreeIdentifier.hpp"

struct ParsingTreeAccessor: public ParsingTreeIdentifier
{
    ParsingTreeAccessor *child; // User -> info -> displayName
};

#endif // PARSINGTREEACCESSOR_HPP
