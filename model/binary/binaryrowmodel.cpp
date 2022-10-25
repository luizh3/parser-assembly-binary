#include "binaryrowmodel.h"

BinaryRowModel::BinaryRowModel() :
    _dsUpcode( "" ),
    _drawRow( "" ),
    _addressMemoryValues( "" ){}

const QString& BinaryRowModel::addressMemoryValues() const {
    return _addressMemoryValues;
}

void BinaryRowModel::setAddressMemoryValues( const QString &newAddressMemoryValues ) {
    _addressMemoryValues = newAddressMemoryValues;
}

const QString &BinaryRowModel::drawRow() const {
    return _drawRow;
}

void BinaryRowModel::setDrawRow( const QString &newDrawRow ) {
    _drawRow = newDrawRow;
}

const QString &BinaryRowModel::dsUpcode() const {
    return _dsUpcode;
}

void BinaryRowModel::setDsUpcode( const QString &newDsUpcode ) {
    _dsUpcode = newDsUpcode;
}
