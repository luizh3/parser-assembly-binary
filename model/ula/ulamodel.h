#ifndef ULAMODEL_H
#define ULAMODEL_H

#include <QList>

class UlaModel {
public:
    UlaModel();
    const QList<QString>& values() const;
    void setValues(const QList<QString>& newValues);

    const QString& result() const;
    void setResult(const QString& newResult);

    const QString& memoryAddress() const;
    void setMemoryAddress( const QString& newMemoryAddress );

private:
    QString _memoryAddress;
    QString _result;
    QList<QString> _values;
};

#endif // ULAMODEL_H
