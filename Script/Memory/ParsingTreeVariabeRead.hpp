#ifndef PARSINGTREEVARIABEREAD_HPP
#define PARSINGTREEVARIABEREAD_HPP

#include "../Types/ParsingTreeValue.hpp"
#include "ParsingTreeAccessor.hpp"
#include "MemoryManagement.hpp"

struct ParsingTreeVariabeRead: public ParsingTreeValue
{

    ParsingTreeAccessor *id;

    ParsingTreeVariabeRead()
    {
        debugName = "ParsingTreeVariabeRead";
    }

    ParsingTreeValue *execute(MemoryManagement *pMemory)
    {
//        qDebug() << "READ";
        executeNext(pMemory);
        return pMemory->readValue(id);
    }
};

#endif // PARSINGTREEVARIABEREAD_HPP
