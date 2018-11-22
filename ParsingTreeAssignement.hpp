#ifndef PARSINGTREEASSIGNEMENT_HPP
#define PARSINGTREEASSIGNEMENT_HPP

#include <QByteArray>
#include "ParsingTreeValue.hpp"
#include "ParsingTreeAccessor.hpp"
#include "ParsingTreeEntryPoint.hpp"
#include "MemoryManagement.hpp"

struct ParsingTreeAssignment: public ParsingTreeEntryPoint
{
    QByteArray symbol;
    ParsingTreeValue *from;
    ParsingTreeAccessor *to;

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory)
    {
        qDebug() << "ASSIGN";

        pMemory->setValue(to, from->execute(pMemory));

        executeNext(pMemory);
        return nullptr;
    }
};

#endif // PARSINGTREEASSIGNEMENT_HPP
