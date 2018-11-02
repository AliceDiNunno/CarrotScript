#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QString>
#include <QThread>
#include <QStack>
#include <QQueue>
#include "BehaviourTree/Sequence.hpp"
#include "BehaviourTree/SequenceNode.h"
#include "ComparisonMethod.hpp"

class SequenceConditionnal;
class Interpreter;
struct OpcodeSet
{
    QString opcode;
    SequenceNode *(Interpreter::*run)(QStringList);
};

class QFile;
class Interpreter: public QThread
{
    Q_OBJECT

public:
    Interpreter();
    ~Interpreter();
    void parseAll(QString );

private:
    void run();

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
    QQueue<QString> _instructions;
    QString _lastInstruction;
    int _scriptPosition;
};

#endif // INTERPRETER_H
