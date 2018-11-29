#ifndef MEMORYMANAGEMENT_HPP
#define MEMORYMANAGEMENT_HPP

#include <QStack>
#include <QVariant>
#include <QMap>
#include <QString>
#include <QtDebug>

#include "MemoryScriptVariable.hpp"
#include "../Binding/ScriptMemoryBinding.hpp"


struct ParsingTreeIdentifier;
class ScriptClassBinding;
class MemoryManagement: public QObject, public ScriptMemoryBinding
{
    Q_OBJECT

public:
    MemoryManagement();
    virtual ~MemoryManagement();

    void reset();

    ParsingTreeValue *callFunction(ParsingTreeAccessor *ids, QList<ParsingTreeValue *>);

    void setValue(ParsingTreeAccessor *name, ParsingTreeValue *);
    ParsingTreeValue *readValue(ParsingTreeAccessor *name);
    static QVariant translateValue(ParsingTreeValue *);

    void insert(ScriptVariable );

    void enterScope();
    void exitScope();

private:
    ParsingTreeValue *readChild(ParsingTreeAccessor *accs, ParsingTreeValue *vp);

signals:
    void message(QString );
    void info(QString );
    void warn(QString );

private:
    QMap<QString, ScriptClassBinding *> bindings;
    QList<QList<ScriptVariable *> *> scopes;
};

#endif // MEMORYMANAGEMENT_HPP
