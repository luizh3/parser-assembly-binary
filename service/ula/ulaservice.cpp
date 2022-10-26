#include "ulaservice.h"

#include <QDebug>

#include <service/memorymanager.h>

namespace {
    constexpr const int NR_SIZE_BITS_VALUE = 10;
}

void UlaService::process( const QList<BinaryRowModel*>& rowsBinary ) const {

    MemoryManager* memoryManager = &MemoryManager::instance();

    for( const BinaryRowModel* binary : rowsBinary ){

        const TipoOperacaoAssemblyEnum tpOperacao = tpOperacaoByDsUpcode( binary->dsUpcode() );
        const QList<QString> values = splitValues( memoryManager->getValuesByAddressMemory( binary->addressMemoryValues() ) );

        switch ( tpOperacao ) {
            case TipoOperacaoAssemblyEnum::ADD:
                sum( values.first(), values.last() );
                break;
            case TipoOperacaoAssemblyEnum::SUB:
                sub( values.first(), values.last() );
                break;
            case TipoOperacaoAssemblyEnum::LOAD:
                break;
            default:
                break;
        }

    }

}

QList<QString> UlaService::splitValues( QString value ) const {

    QList<QString> values = {};

    while( !value.isEmpty() ){
        values.append( value.left( NR_SIZE_BITS_VALUE ) );
        value.remove( 0, NR_SIZE_BITS_VALUE );
    }

    return values;

}

TipoOperacaoAssemblyEnum UlaService::tpOperacaoByDsUpcode( const QString& dsUpcode ) const {

    const QMap<QString, TipoOperacaoAssemblyEnum> dsOperacaoByTp = {
        { "00001", TipoOperacaoAssemblyEnum::ADD },
        { "00002", TipoOperacaoAssemblyEnum::LOAD },
        { "00003", TipoOperacaoAssemblyEnum::SUB },
    };

    return dsOperacaoByTp.value( dsUpcode, TipoOperacaoAssemblyEnum::UNDEFINED );
}

void UlaService::sum( const QString &first, const QString &second ) const {

    qDebug() << " UlaService::sum [FIRST]" << first << "[SECOND]" << second;

    QString result = "";
    bool hasRest = false;

    for( int index = 0; index < NR_SIZE_BITS_VALUE; index++ ){

        const int firstNum = first[1].digitValue();
        const int secondNum = second[1].digitValue();

        if( !( firstNum - secondNum ) ){
            hasRest = true;
            result.append(0);
        }

    }

}

void UlaService::sub( const QString &first, const QString &second ) const {

    qDebug() << " UlaService::sum [FIRST]" << first << "[SECOND]" << second;

}
