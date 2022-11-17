#include "variablemodel.h"

#include <model/helper/instructionhelper.h>

VariableModel::VariableModel() :
    _register( nullptr ),
    _tpOperation( TipoOperacaoAssemblyEnum::UNDEFINED ),
    _value( 0 ),
    _isLabel( false ),
    _type( "" ),
    _params( {} ){}

VariableModel::VariableModel( const VariableModel *variable ) :
    _value( variable->value() ),
    _isLabel( variable->isLabel() ),
    _type( variable->type() ),
    _params( variable->params() ){
}

VariableModel::TypeVariableEnum VariableModel::tpVariable() {
    return TypeVariableEnum::VARIABLE;
}

QList<QString> VariableModel::paramsWithoutOperators() const {

    QList<QString> params = {};

    for( const QString& param : qAsConst( _params ) ){
        if( !InstructionHelper::allOperators().contains( param ) ){
            params.append( param );
        }
    }

    return params;

}

TipoOperacaoAssemblyEnum VariableModel::tpOperation( const bool isAlreadyAllocated ) const {

    if( _tpOperation != TipoOperacaoAssemblyEnum::UNDEFINED ){
        return _tpOperation;
    }

    if( _params.contains("/") ){
        return TipoOperacaoAssemblyEnum::DIV;
    }

    if( _params.contains("*") ){
        return TipoOperacaoAssemblyEnum::MUL;
    }

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

    if( _params.contains("=" ) && isAlreadyAllocated ){
        return TipoOperacaoAssemblyEnum::MOV;
    }

    return TipoOperacaoAssemblyEnum::LOAD;

}

void VariableModel::addParam(const QList<QString> &params) {
    _params.append( params );
}

void VariableModel::addParam( const QString &param ) {
    _params.append( param );
}

QList<QString> VariableModel::params() const {
    return _params;
}

void VariableModel::clearParams() {
    _params.clear();
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

bool VariableModel::isLabel() const {
    return _isLabel;
}

void VariableModel::setIsLabel( bool newIsLabel ) {
    _isLabel = newIsLabel;
}

void VariableModel::setTpOperation( const TipoOperacaoAssemblyEnum& tpOperation ) {
    _tpOperation = tpOperation;
}
