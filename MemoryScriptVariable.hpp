#ifndef MEMORYSCRIPTVARIABLE_HPP
#define MEMORYSCRIPTVARIABLE_HPP

#include <QPair>
#include <QByteArray>
#include "ParsingTreeValue.hpp"

using ScriptVariable = QPair<QByteArray, ParsingTreeValue *>;

#endif // MEMORYSCRIPTVARIABLE_HPP
