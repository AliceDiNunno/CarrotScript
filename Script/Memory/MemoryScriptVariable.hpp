#ifndef MEMORYSCRIPTVARIABLE_HPP
#define MEMORYSCRIPTVARIABLE_HPP

#include <QPair>
#include <QByteArray>

struct ParsingTreeValue;
using ScriptVariable = QPair<QByteArray, ParsingTreeValue *>;

#endif // MEMORYSCRIPTVARIABLE_HPP
