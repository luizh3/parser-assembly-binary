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
    QString getValuesByAddressMemory( const QString& address ) const;

    void reset();

private:
    QString allocBinaryMemory();

    int _currentMemoryBinary;
    QString _currentMemoryAssembly;
    QMap<QString, QString> _valuesByAddress;
};

#endif // MEMORYMANAGER_H
