#include "parsercontroller.h"

#include <service/parser/parserservice.h>

void ParserController::makeParser( QString dsCodeInC ) {

    const ParserResultModel* parserResult = ParserService().makeParser( dsCodeInC );

    setDsCodeResultAssembly( parserResult->dsCodeResultAssembly() );
    setDsCodeResultBinary( parserResult->dsCodeResultBinary() );
    setDsCodeResultUla( parserResult->dsCodeResultUla() );
    setDsCodeInputC( dsCodeInC );

    delete parserResult;

    emit parserFnished();

}

const QString& ParserController::dsCodeInputC() const {
    return _dsCodeInputC;
}

void ParserController::setDsCodeInputC( const QString& newDsCodeInputC ) {

    if (_dsCodeInputC == newDsCodeInputC){
         return;
    }

    _dsCodeInputC = newDsCodeInputC;
    emit dsCodeInputCChanged();

}

const QString &ParserController::dsCodeResultAssembly() const {
    return _dsCodeResultAssembly;
}

void ParserController::setDsCodeResultAssembly( const QString &newDsCodeResultAssembly ) {

    if ( _dsCodeResultAssembly == newDsCodeResultAssembly ){
        return;
    }

    _dsCodeResultAssembly = newDsCodeResultAssembly;
    emit dsCodeResultAssemblyChanged();
}

const QString &ParserController::dsCodeResultBinary() const {
    return _dsCodeResultBinary;
}

void ParserController::setDsCodeResultBinary( const QString &newDsCodeResultBinary ) {

    if (_dsCodeResultBinary == newDsCodeResultBinary){
        return;
    }

    _dsCodeResultBinary = newDsCodeResultBinary;
    emit dsCodeResultBinaryChanged();
}

const QString& ParserController::dsCodeResultUla() const {
    return _dsCodeResultUla;
}

void ParserController::setDsCodeResultUla( const QString& newDsCodeResultUla ) {

    if (_dsCodeResultUla == newDsCodeResultUla ){
        return;
    }

    _dsCodeResultUla = newDsCodeResultUla;
    emit dsCodeResultUlaChanged();

}
