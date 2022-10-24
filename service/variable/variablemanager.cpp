#include "variablemanager.h"

VariableManager::VariableManager() :
    _variables( {} ){}

VariableManager::~VariableManager() {
    qDeleteAll( _variables );
}

VariableManager &VariableManager::instance() {
    static VariableManager mariableManager;
    return mariableManager;
}

VariableModel *VariableManager::get( const QString &name ) const {
    return _variables.value( name, nullptr );
}

void VariableManager::add( const QString &name, VariableModel *variable ) {
    _variables.insert( name, variable );
}

QList<VariableModel *> VariableManager::getAll() const {
    return _variables.values();
}

QList<QString> VariableManager::getAllKeys() const{
    return _variables.keys();
}
