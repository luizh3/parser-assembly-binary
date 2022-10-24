#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <QMap>
#include <QString>

class MemoryManager {
public:
    MemoryManager();

    static MemoryManager& instance();

    QString alloc();
    QString allocValues( const QList<QString>& values );

private:
    QString _currentAddress;
    QMap<QString, QString> _valuesByAddress;
};

#endif // MEMORYMANAGER_H
