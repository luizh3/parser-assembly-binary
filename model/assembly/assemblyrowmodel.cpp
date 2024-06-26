#include "assemblyrowmodel.h"

AssemblyRowModel::AssemblyRowModel() :
    _variableResultOperation( nullptr ),
    _typeOperation( TipoOperacaoAssemblyEnum::UNDEFINED ),
    _rawTextRow( "" ),
    _addressMemoryRow( "" ),
    _values( {} ){
}

TipoOperacaoAssemblyEnum AssemblyRowModel::typeOperation() const {
    return _typeOperation;
}

void AssemblyRowModel::setTypeOperation( TipoOperacaoAssemblyEnum newTypeOperation ) {
    _typeOperation = newTypeOperation;
}

const QList<QString>& AssemblyRowModel::values() const {
    return _values;
}

void AssemblyRowModel::setValues( const QList<QString>& newValues ) {
    _values = newValues;
}

const QString& AssemblyRowModel::rawTextRow() const {
    return _rawTextRow;
}

void AssemblyRowModel::setRawTextRow( const QString& newRawTextLinha ) {
    _rawTextRow = newRawTextLinha;
}

const QString& AssemblyRowModel::addressMemoryRow() const{
    return _addressMemoryRow;
}

void AssemblyRowModel::setAddressMemoryRow( const QString& newAddressMemoryRow ) {
    _addressMemoryRow = newAddressMemoryRow;
}

VariableModel* AssemblyRowModel::variableResultOperation() const {
    return _variableResultOperation;
}

void AssemblyRowModel::setVariableResultOperation( VariableModel* newVariableResultOperation ) {
    _variableResultOperation = newVariableResultOperation;
}

bool AssemblyRowModel::isSkip() const {
    return _isSkip;
}

void AssemblyRowModel::setIsSkip( bool newIsSkip ) {
    _isSkip = newIsSkip;
}

