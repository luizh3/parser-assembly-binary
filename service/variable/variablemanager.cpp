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

VariableModel *VariableManager::getByRegisterName( const QString &name ) const {
    return variableByRegister().value( name, nullptr );
}

void VariableManager::add( const QString &name, VariableModel *variable ) {
    _nameVariablesOrder.append( name );
    _variables.insert( name, variable );
}

QList<VariableModel *> VariableManager::getAll() const {
    return _variables.values();
}

QList<QString> VariableManager::getAllKeys() const{
    return _nameVariablesOrder;
}

QMap<QString, VariableModel*> VariableManager::variableByRegister() const {

    QMap<QString,VariableModel*> values = {};

    for( VariableModel* variable : qAsConst( _variables ) ){

        if( !variable->getRegister() ){
            continue;
        }

        values.insert( variable->getRegister()->nameRegister(), variable );

    }

    return values;

}

QList<QString> VariableManager::registersVariables() const {
    return variableByRegister().keys();
}

void VariableManager::addNameVariable( const QString &name ) {
    _nameVariablesOrder.append( name );
}
