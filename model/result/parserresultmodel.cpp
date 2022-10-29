#include "parserresultmodel.h"

ParserResultModel::ParserResultModel() :
    _dsCodeResultUla(""),
    _dsCodeResultBinary(""),
    _dsCodeResultAssembly(""){}

const QString& ParserResultModel::dsCodeResultUla() const {
    return _dsCodeResultUla;
}

void ParserResultModel::setDsCodeResultUla( const QString& newDsCodeResultUla ) {
    _dsCodeResultUla = newDsCodeResultUla;
}

const QString& ParserResultModel::dsCodeResultBinary() const {
    return _dsCodeResultBinary;
}

void ParserResultModel::setDsCodeResultBinary( const QString& newDsCodeResultBinary ) {
    _dsCodeResultBinary = newDsCodeResultBinary;
}

const QString& ParserResultModel::dsCodeResultAssembly() const {
    return _dsCodeResultAssembly;
}

void ParserResultModel::setDsCodeResultAssembly( const QString& newDsCodeResultAssembly ) {
    _dsCodeResultAssembly = newDsCodeResultAssembly;
}
