#include "variablemodel.h"

#include <model/helper/instructionhelper.h>

VariableModel::VariableModel() :
    _value( 0 ),
    _type( "" ),
    _registerName( "" ),
    _params( {} ){}

QList<QString> VariableModel::paramsWithoutOperators() const {

    QList<QString> params = {};

    for( const QString& param : _params ){
        if( !InstructionHelper::allOperators().contains( param ) ){
            params.append( param );
        }
    }

    return params;

}

TipoOperacaoAssemblyEnum VariableModel::tpOperation() const {

    if( _params.contains("+") ){
        return TipoOperacaoAssemblyEnum::ADD;
    }

    if( _params.contains("-") ){
        return TipoOperacaoAssemblyEnum::SUB;
    }

    return TipoOperacaoAssemblyEnum::LOAD;

}

const QString &VariableModel::registerName() const {
    return _registerName;
}

void VariableModel::setRegisterName(const QString &registerName) {
    _registerName = registerName;
}

void VariableModel::addParam(const QString &param) {
    _params.append( param );
}

int VariableModel::value() const {
    return _value;
}

void VariableModel::setValue( int newValue ) {
    _value = newValue;
}

const QString &VariableModel::type() const {
    return _type;
}

void VariableModel::setType( const QString &newType ) {
    _type = newType;
}
