#ifndef MEMORYMANAGEMENT_HPP
#define MEMORYMANAGEMENT_HPP

#include <QStack>
#include <QVariant>
#include <QMap>
#include <QString>
#include <QtDebug>

#include "MemoryScriptVariable.hpp"
#include "ScriptMemoryBinding.hpp"
#include "ScriptClassBinding.hpp"

class MemoryManagement: public QObject, public ScriptMemoryBinding
{
    Q_OBJECT

public:
    virtual ~MemoryManagement();
    MemoryManagement();

    ParsingTreeValue *readValue(ParsingTreeAccessor *name);

    ParsingTreeValue *callFunction(ParsingTreeIdentifier *ids, QList<ParsingTreeValue *>);

    void setValue(ParsingTreeAccessor *name, ParsingTreeValue *);
    static QVariant translateValue(ParsingTreeValue *);

    void enterScope();
    void exitScope();

private:
    void insert(ScriptVariable );
    ParsingTreeValue *readChild(ParsingTreeAccessor *accs, ParsingTreeValue *vp);

signals:
    void message(QString );
    void info(QString );
    void warn(QString );

private:
    QMap<QByteArray, ScriptClassBinding *> bindings;
    QList<QList<ScriptVariable *> *> scopes;
};

#endif // MEMORYMANAGEMENT_HPP
