#ifndef MEMORYMANAGEMENT_HPP
#define MEMORYMANAGEMENT_HPP

#include <QStack>
#include <QVariant>
#include <QString>
#include <QtDebug>

class MemoryManagement
{
public:
    MemoryManagement();
    void set(QString key, QVariant value)
    {
        if (!variables.contains(key) && variableScope.count() > 0)
        {
             variableScope.top().append(key);
        }
        variables.insert(key, value);
    }

    QVariant get(QString value)
    {
        qDebug() << variables;
        return variables.value(value);
    }

    void enterScope()
    {
        variableScope.push(QStringList());
    }

    void exitScope()
    {
        QStringList scope = variableScope.pop();
        for (int iScope = 0; iScope < scope.count(); iScope++)
            variables.remove(scope.at(iScope));
    }

private:
    QMap<QString, QVariant> variables;
    QStack<QStringList> variableScope;
};

#endif // MEMORYMANAGEMENT_HPP
