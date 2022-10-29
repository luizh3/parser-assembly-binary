#ifndef BINARYROWMODEL_H
#define BINARYROWMODEL_H

#include <QString>

class BinaryRowModel {
public:
    BinaryRowModel();

    const QString& addressMemoryValues() const;
    void setAddressMemoryValues(const QString &newAddressMemoryValues);

    const QString& rawRow() const;
    void setRawRow( const QString &newRawRow );

    const QString& dsUpcode() const;
    void setDsUpcode(const QString &newDsUpcode);

    const QString& resultValue() const;
    void setResultValue(const QString &newResultValue);

private:
    QString _dsUpcode;
    QString _rawRow;
    QString _addressMemoryValues;
    QString _resultValue;
};

#endif // BINARYROWMODEL_H
