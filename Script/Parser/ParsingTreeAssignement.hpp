#ifndef PARSINGTREEASSIGNEMENT_HPP
#define PARSINGTREEASSIGNEMENT_HPP

#include <QByteArray>
#include "../Types/ParsingTreeValue.hpp"
#include "../Memory/ParsingTreeAccessor.hpp"
#include "ParsingTreeEntryPoint.hpp"
#include "../Memory/MemoryManagement.hpp"

struct ParsingTreeAssignment: public ParsingTreeEntryPoint
{
    QByteArray symbol;
    ParsingTreeValue *from;
    ParsingTreeAccessor *to;

    ParsingTreeAssignment()
    {
        debugName = "ParsingTreeAssignment";
    }

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory)
    {
        //qDebug() << "ASSIGN";

        pMemory->setValue(to, from->execute(pMemory));

        executeNext(pMemory);
        return nullptr;
    }
};

#endif // PARSINGTREEASSIGNEMENT_HPP
