#include "parsercontroller.h"

#include <QMetaEnum>

#include <service/log/logulamanager.h>
#include <service/parser/parserservice.h>
#include <service/binary/binaryservice.h>

void ParserController::makeParser( QString dsCodeInC ) {

    const ParserResultModel* parserResult = ParserService().makeParser( dsCodeInC );

    setDsCodeResultAssembly( parserResult->dsCodeResultAssembly() );
    setDsCodeResultBinary( parserResult->dsCodeResultBinary() );
    setDsCodeResultUla( parserResult->dsCodeResultUla() );
    setDsCodeInputC( dsCodeInC );
    setDsDetailsUla( LogUlaManager::instance().logFormated() );
    setDsSubtitle( subtitleUpCode() );

    delete parserResult;

    emit parserFnished();

}

QString ParserController::subtitleUpCode() const {

    QString subititle;
    QString dsEnum;

    QMap<TipoOperacaoAssemblyEnum, QString> map = BinaryService().mapDsUpCodeByTp();
    QList<TipoOperacaoAssemblyEnum> keys = map.keys();

    for( const TipoOperacaoAssemblyEnum& key : qAsConst( keys )){
      dsEnum = QMetaEnum::fromType<TipoOperacaoAssemblyEnum>().valueToKey( static_cast<int>(key) );
      subititle.append( QString("%0 - %1 %2").arg( map[key], dsEnum, "\n") );
    }

    return subititle;

}

const QString &ParserController::dsDetailsUla() const {
    return _dsDetailsUla;
}

void ParserController::setDsDetailsUla(const QString &newDsDetailsUla) {
    _dsDetailsUla = newDsDetailsUla;
    emit dsDetailsUlaChanged();
}

const QString &ParserController::dsSubtitle() const {
    return _dsSubtitle;
}

void ParserController::setDsSubtitle(const QString &newDsSubtitle) {
    _dsSubtitle = newDsSubtitle;
    emit dsSubtitleChanged();
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
