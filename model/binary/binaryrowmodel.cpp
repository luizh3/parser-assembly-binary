#include "binaryrowmodel.h"

BinaryRowModel::BinaryRowModel() :
    _dsUpcode( "" ),
    _rawRow( "" ),
    _addressMemoryValues( "" ),
    _resultValue( "" ){}

const QString& BinaryRowModel::addressMemoryValues() const {
    return _addressMemoryValues;
}

void BinaryRowModel::setAddressMemoryValues( const QString& newAddressMemoryValues ) {
    _addressMemoryValues = newAddressMemoryValues;
}

const QString& BinaryRowModel::rawRow() const {
    return _rawRow;
}

void BinaryRowModel::setRawRow( const QString& newDrawRow ) {
    _rawRow = newDrawRow;
}

const QString& BinaryRowModel::dsUpcode() const {
    return _dsUpcode;
}

void BinaryRowModel::setDsUpcode( const QString &newDsUpcode ) {
    _dsUpcode = newDsUpcode;
}

const QString& BinaryRowModel::resultValue() const {
    return _resultValue;
}

void BinaryRowModel::setResultValue( const QString& newResultValue ) {
    _resultValue = newResultValue;
}
