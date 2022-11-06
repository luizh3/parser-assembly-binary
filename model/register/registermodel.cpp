#include "registermodel.h"

RegisterModel::RegisterModel( const QString& name ) :
    _fgActive( false ),
    _nameRegister( name ){}

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
