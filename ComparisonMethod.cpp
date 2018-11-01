#include "ComparisonMethod.hpp"

bool isEqual(QVariant a, QVariant b) {
    return a.operator==(b);
}
bool isDifferent(QVariant a, QVariant b) {
    return !isEqual(a, b);
}
bool isLesserThan(QVariant a, QVariant b) {
    return a.operator<(b);
}
bool isGreaterThan(QVariant a, QVariant b) {
    return a.operator>(b);
}
bool isGreaterOrEqual(QVariant a, QVariant b) {
    return !isLesserThan(a, b);
}
bool isLesserOrEqual(QVariant a, QVariant b) {
    return !isGreaterThan(a, b);
}
