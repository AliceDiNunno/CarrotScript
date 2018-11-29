#ifndef PARSINGTREEFUNCTIONDECLARATION_HPP
#define PARSINGTREEFUNCTIONDECLARATION_HPP

#include <QList>
#include <QByteArray>
#include <QDebug>
#include "ParsingTreeEntryPoint.hpp"

struct ParsingTreeFunctionDeclaration: public ParsingTreeEntryPoint
{
    ParsingTreeFunctionDeclaration();

    virtual ParsingTreeValue *execute(MemoryManagement *pMemory);

    QByteArray name;
    QList<QByteArray> variableNames;
};

#endif // PARSINGTREEFUNCTIONDECLARATION_HPP
