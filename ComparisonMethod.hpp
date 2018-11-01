#ifndef COMPARISONMETHOD_HPP
#define COMPARISONMETHOD_HPP

#include <QObject>
#include <QVariant>

struct ComparisonMethod
{
    QString ComparisonOperator;
    bool (*compare)(QVariant, QVariant);
};

extern "C" {
    bool isEqual(QVariant a, QVariant b);
    bool isDifferent(QVariant a, QVariant b);
    bool isLesserThan(QVariant a, QVariant b);
    bool isGreaterThan(QVariant a, QVariant b);
    bool isGreaterOrEqual(QVariant a, QVariant b);
    bool isLesserOrEqual(QVariant a, QVariant b);
}

#endif // COMPARISONMETHOD_HPP
