#ifndef BINARYROWMODEL_H
#define BINARYROWMODEL_H

#include <QString>

class BinaryRowModel {
public:
    BinaryRowModel();

    const QString &addressMemoryValues() const;
    void setAddressMemoryValues(const QString &newAddressMemoryValues);

    const QString &drawRow() const;
    void setDrawRow( const QString &newDrawRow );

    const QString &dsUpcode() const;
    void setDsUpcode(const QString &newDsUpcode);

private:
    QString _dsUpcode;
    QString _drawRow;
    QString _addressMemoryValues;
};

#endif // BINARYROWMODEL_H
