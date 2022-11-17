#include "registermanager.h"

#include <service/memorymanager.h>

RegisterManager::RegisterManager() :
    _registersAlloc( { "RA", "RB", "RC", "RD", "RE", "RF", "RG", "RH", "RI", "RJ", "RK", "RL", "RM" } ) {
    init();
}

RegisterManager::~RegisterManager() {
    qDeleteAll( _registers );
}

RegisterManager &RegisterManager::instance() {
    static RegisterManager registerManager;
    return registerManager;
}

RegisterModel* RegisterManager::getOne() {

    RegisterModel* firstRegister = _registers.takeAt( 0 );

    if( firstRegister->isActive() ){
        throw std::bad_alloc();
    }

    firstRegister->setFgActive( true );
    _registers.append( firstRegister );

    return firstRegister;
}

bool RegisterManager::hasRegisterByName( const QString &name ) const {
    return _registersAlloc.contains( name );
}

void RegisterManager::reset() {
    qDeleteAll( _registers );
    _registers.clear();
    init();
}

void RegisterManager::free( RegisterModel* registerFree ) {
    RegisterModel* current = _registers.takeAt( _registers.indexOf( registerFree ) );
    current->setFgActive( false );
    _registers.prepend( current );
}

void RegisterManager::init() {
    for( const QString& registerName : qAsConst( _registersAlloc ) ){
        _registers.append( new RegisterModel( registerName, MemoryManager::instance().allocBinaryMemory() ) );
    }
}
