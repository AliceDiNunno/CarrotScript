#ifndef PARSINGTREEFUNCTIONDECLARATION_HPP
#define PARSINGTREEFUNCTIONDECLARATION_HPP

#include <QList>
#include <QByteArray>
#include <QDebug>
#include "ParsingTreeEntryPoint.hpp"

struct ParsingTreeFunctionDeclaration: public ParsingTreeEntryPoint
{
    QByteArray name;
    QList<QByteArray> variableNames;

    ParsingTreeFunctionDeclaration()
    {
        debugName = "ParsingTreeFunctionDeclaration";
    }

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory)
    {
        //qDebug() << "Declare function";
        executeNext(pMemory);
        return nullptr;
    }
};

#endif // PARSINGTREEFUNCTIONDECLARATION_HPP
