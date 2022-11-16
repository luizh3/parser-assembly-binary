#include "ulaservice.h"

#include <QDebug>

#include <service/memorymanager.h>

namespace {
    constexpr const int NR_SIZE_INT = 10;
    constexpr const int NR_BASE_BINARY = 2;
    constexpr const int NR_SIZE_BITS_VALUE = 10;
    constexpr const int NR_SIZE_FOR = 9;
}

UlaModel* UlaService::process( const BinaryRowModel* binary ) const {

    MemoryManager* memoryManager = &MemoryManager::instance();
    const TipoOperacaoAssemblyEnum tpOperacao = tpOperacaoByDsUpcode( binary->dsUpcode() );
    const QList<QString> values = splitValues( memoryManager->getValuesByAddressMemory( binary->addressMemoryValues() ) );

    QString resultOperation = "";

    switch ( tpOperacao ) {
        case TipoOperacaoAssemblyEnum::ADD:
            resultOperation = sum( values.first(), values.last() );
            break;
        case TipoOperacaoAssemblyEnum::SUB:
            resultOperation = sub( values.first(), values.last() );
            break;
        case TipoOperacaoAssemblyEnum::BGE:
            resultOperation = bge( values.first(), values.last() );
            break;
        case TipoOperacaoAssemblyEnum::BLE:
            resultOperation = ble( values.first(), values.last() );
            break;
        case TipoOperacaoAssemblyEnum::BEQ:
            resultOperation = beq( values.first(), values.last() );
            break;
        case TipoOperacaoAssemblyEnum::BGT:
            resultOperation = bgt( values.first(), values.last() );
            break;
        case TipoOperacaoAssemblyEnum::BLT:
            resultOperation = blt( values.first(), values.last() );
            break;
        case TipoOperacaoAssemblyEnum::BNE:
            resultOperation = bne( values.first(), values.last() );
            break;
        case TipoOperacaoAssemblyEnum::LOAD:
            break;
        default:
            break;
     }

    UlaModel* ulaModel = new UlaModel();
    ulaModel->setMemoryAddress( binary->addressMemoryValues() );
    ulaModel->setResult( resultOperation );
    ulaModel->setValues( values );
    ulaModel->setTpOperacao( tpOperacao );

    return ulaModel;
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
        { "00001", TipoOperacaoAssemblyEnum::LOAD },
        { "00010", TipoOperacaoAssemblyEnum::ADD },
        { "00011", TipoOperacaoAssemblyEnum::SUB },
        { "00100", TipoOperacaoAssemblyEnum::BGE },
        { "00101", TipoOperacaoAssemblyEnum::BLE },
        { "00110", TipoOperacaoAssemblyEnum::BEQ },
        { "00111", TipoOperacaoAssemblyEnum::BGT },
        { "01000", TipoOperacaoAssemblyEnum::BLT },
        { "01001", TipoOperacaoAssemblyEnum::BNE },
        { "01010", TipoOperacaoAssemblyEnum::JUMP },
        { "01011", TipoOperacaoAssemblyEnum::LABEL },
        { "01100", TipoOperacaoAssemblyEnum::MOV },
    };

    return dsOperacaoByTp.value( dsUpcode, TipoOperacaoAssemblyEnum::UNDEFINED );
}

QString UlaService::sum( const QString& first, const QString& second ) const {

    qDebug() << " UlaService::sum [FIRST]" << first << "[SECOND]" << second;

    int nrFirst = first.toInt();
    int nrSecond = second.toInt();

    int rest = 0;
    QString sum = "";

    while( nrFirst != 0 || nrSecond != 0 )  {

        sum.prepend( QString::number( ( ( nrFirst % NR_SIZE_INT ) + ( nrSecond % NR_SIZE_INT ) + rest ) % NR_BASE_BINARY )[0] );

        rest = (int)( ( ( nrFirst % NR_SIZE_INT ) + ( nrSecond % NR_SIZE_INT ) + rest ) / NR_BASE_BINARY );

        nrFirst /= NR_SIZE_INT;
        nrSecond /= NR_SIZE_INT;

    }

    if ( rest != 0 ) {
        sum.prepend( QString::number( rest )[0] ) ;
    }

    return sum;
}

QString UlaService::sub( const QString &first, const QString &second ) const {

    qDebug() << " UlaService::sum [FIRST]" << first << "[SECOND]" << second;

    return "0";

}

QString UlaService::bge( const QString &first, const QString &second ) const {
    for(int index = NR_SIZE_FOR; index >= 0; index--){
        if(first[index] < second[index]) {
            return "0";
        }
    }

    return "1";
}

QString UlaService::ble(const QString &first, const QString &second) const {
    for(int index = NR_SIZE_FOR; index >= 0; index--){
        if(first[index] > second[index]) {
            return "0";
        }
    }

    return "1";
}

QString UlaService::beq(const QString &first, const QString &second) const {

    for(int index = NR_SIZE_FOR; index >= 0; index--){
        if(first[index] != second[index]) {
            return "0";
        }
    }

    return "1";
}

QString UlaService::bgt(const QString &first, const QString &second) const {

    for(int index = NR_SIZE_FOR; index >= 0; index--){
        if(first[index] < second[index]) {
            return "0";
        }
    }

    return "1";
}

QString UlaService::blt(const QString &first, const QString &second) const {

    for(int index = NR_SIZE_FOR; index >= 0; index--){
        if(first[index] > second[index]) {
            return "0";
        }
    }

    return "1";
}

QString UlaService::bne(const QString &first, const QString &second) const {

    for(int index = NR_SIZE_FOR; index >= 0; index--){
        if(first[index] != second[index]) {
            return "1";
        }
    }

    return "0";
}
