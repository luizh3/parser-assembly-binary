#include "binaryrowmodel.h"

BinaryRowModel::BinaryRowModel() :
    _dsUpcode( "" ),
    _rawRow( "" ),
    _addressMemoryValues( "" ){}

const QString& BinaryRowModel::addressMemoryValues() const {
    return _addressMemoryValues;
}

void BinaryRowModel::setAddressMemoryValues( const QString &newAddressMemoryValues ) {
    _addressMemoryValues = newAddressMemoryValues;
}

const QString &BinaryRowModel::rawRow() const {
    return _rawRow;
}

void BinaryRowModel::setRawRow( const QString &newDrawRow ) {
    _rawRow = newDrawRow;
}

const QString &BinaryRowModel::dsUpcode() const {
    return _dsUpcode;
}

void BinaryRowModel::setDsUpcode( const QString &newDsUpcode ) {
    _dsUpcode = newDsUpcode;
}
