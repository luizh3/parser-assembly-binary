#include "ulamodel.h"

UlaModel::UlaModel() {}

const QList<QString>& UlaModel::values() const {
    return _values;
}

void UlaModel::setValues( const QList<QString>& newValues ) {
    _values = newValues;
}

const QString& UlaModel::result() const {
    return _result;
}

void UlaModel::setResult( const QString& newResult ) {
    _result = newResult;
}

const QString& UlaModel::memoryAddress() const {
    return _memoryAddress;
}

void UlaModel::setMemoryAddress( const QString& newMemoryAddress ) {
    _memoryAddress = newMemoryAddress;
}
