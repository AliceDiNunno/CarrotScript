#ifndef SEQUENCENODE_H
#define SEQUENCENODE_H

#include <QVariant>
#include <QUuid>

class MemoryManagement;
using SequenceFunction = std::function<bool (MemoryManagement *)>;

class SequenceNode {
public:
    SequenceNode();
    virtual ~SequenceNode();

    virtual bool canRun() = 0;
    virtual bool run(MemoryManagement *apMemory) = 0;

    QStringList arguments;
};

#endif // SEQUENCENODE_H
