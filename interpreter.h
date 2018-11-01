#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QString>
#include <QThread>
#include <QStack>
#include "BehaviourTree/Sequence.hpp"
#include "BehaviourTree/SequenceNode.h"

class SequenceConditionnal;
class Interpreter;

struct OpcodeSet
{
    QString opcode;
    SequenceNode *(Interpreter::*run)(QStringList);
};

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

class QFile;
class Interpreter: public QThread
{
    Q_OBJECT

public:
    Interpreter();
    ~Interpreter();
    void loadFile(QString aFileName);

private:
    void run();
    void parseAll(QString );

    SequenceNode *parseNext();
    bool compare(QVariant a, QVariant b, QString comparisonOperator);
    QVariant getValue(QString, MemoryManagement *pMemory);

private: //opcode function
    SequenceNode *opcAdd(QStringList);
    SequenceNode *opcSet(QStringList);
    SequenceNode *opcMessage(QStringList);

    //Conditionnal
    SequenceNode *opcIf(QStringList);
    SequenceNode *opcWhile(QStringList);

    //Endconditionnal (TODO: Should error if no While/If
    SequenceNode *opcElse(QStringList); //TODO: should error if in while
    SequenceNode *opcEnd(QStringList);

signals:
    void info(QString);
    void alert(QString);
    void error(QString);
    void message(QString);

private: //Running
    QList<OpcodeSet> _opcodes;
    QList<ComparisonMethod> _comparisonMethods;
    QStack<SequenceConditionnal *> _conditionnals;
    Sequence *_pSequence;

private: //Parsing
    QStringList _instructions;
    QString _lastInstruction;
    int _scriptPosition;
};

#endif // INTERPRETER_H
