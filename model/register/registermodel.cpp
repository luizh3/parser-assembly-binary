#include "registermodel.h"

RegisterModel::RegisterModel( const QString& name, const QString& memory ) :
    _fgActive( false ),
    _nameRegister( name ),
    _binaryMemory(memory){}

const QString& RegisterModel::nameRegister() const {
    return _nameRegister;
}

void RegisterModel::setNameRegister( const QString& newNameRegister ) {
    _nameRegister = newNameRegister;
}

bool RegisterModel::isActive() const {
    return _fgActive;
}

void RegisterModel::setFgActive( bool newFgActive ) {
    _fgActive = newFgActive;
}

const QString &RegisterModel::binaryMemory() const {
    return _binaryMemory;
}

void RegisterModel::setBinaryMemory(const QString &newBinaryMemory){
    _binaryMemory = newBinaryMemory;
}
