#include "registermanager.h"

#include <new>

RegisterManager::RegisterManager() :
    _registersAlloc( { "RA", "RB", "RC", "RD", "RE", "RJ" } ) {

    for( const QString& registerName : qAsConst( _registersAlloc ) ){
        _registers.append( new RegisterModel( registerName ) );
    }
}

RegisterManager::~RegisterManager() {
    qDeleteAll( _registers );
}

RegisterManager &RegisterManager::instance() {
    static RegisterManager registerManager;
    return registerManager;
}

// TODO criar um register model
// Criar uma fg de utilizado

RegisterModel* RegisterManager::getOne() {

    RegisterModel* firstRegister = _registers.takeAt( 0 );

    if( firstRegister->isActive() ){
        throw std::bad_alloc();
    }

    firstRegister->setFgActive( true );
    _registers.append( firstRegister );

    return firstRegister;
}

const QList<RegisterModel*>& RegisterManager::registers() const {
    return _registers;
}

void RegisterManager::setRegisters( const QList<RegisterModel*>& newRegisters ) {
    _registers = newRegisters;
}
