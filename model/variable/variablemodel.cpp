#include "variablemodel.h"

#include <model/helper/instructionhelper.h>

VariableModel::VariableModel() :
    _register( nullptr ),
    _value( 0 ),
    _isLabel( false ),
    _type( "" ),
    _params( {} ){}

QList<QString> VariableModel::paramsWithoutOperators() const {

    QList<QString> params = {};

    for( const QString& param : qAsConst( _params ) ){
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

    if( _params.contains("==") ){
        return TipoOperacaoAssemblyEnum::BEQ;
    }

    if( _params.contains(">=") ){
        return TipoOperacaoAssemblyEnum::BGE;
    }

    if( _params.contains("<=") ){
        return TipoOperacaoAssemblyEnum::BLE;
    }

    if( _params.contains(">") ){
        return TipoOperacaoAssemblyEnum::BGT;
    }

    if( _params.contains("<") ){
        return TipoOperacaoAssemblyEnum::BLT;
    }

    if( _params.contains("!=") ){
        return TipoOperacaoAssemblyEnum::BNE;
    }

    return TipoOperacaoAssemblyEnum::LOAD;

}

void VariableModel::addParam(const QList<QString> &params) {
    _params.append( params );
}

void VariableModel::addParam( const QString &param ) {
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

RegisterModel* VariableModel::getRegister() const {
    return _register;
}

void VariableModel::setRegister( RegisterModel* newRegister ){
    _register = newRegister;
}

bool VariableModel::isLabel() const
{
    return _isLabel;
}

void VariableModel::setIsLabel(bool newIsLabel)
{
    _isLabel = newIsLabel;
}
