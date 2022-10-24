#include "registermanager.h"

RegisterManager::RegisterManager() :
    _nameRegisters( { "RA", "RB", "RC", "RD", "RE", "RJ" } ) {}

RegisterManager &RegisterManager::instance() {
    static RegisterManager registerManager;
    return registerManager;
}

// TODO criar um register model
// Criar uma fg de utilizado

QString RegisterManager::getOne() {
    const QString current = _nameRegisters.first();
    _nameRegisters.removeFirst();
    return current;
}
