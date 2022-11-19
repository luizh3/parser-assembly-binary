#include "ulaservice.h"

#include <QDebug>

#include <service/memorymanager.h>
#include <service/label/labelmanager.h>
#include <service/log/logulamanager.h>

namespace {
    constexpr const int NR_SIZE_INT = 10;
    constexpr const int NR_BASE_BINARY = 2;
    constexpr const int NR_SIZE_BITS_VALUE = 10;
    constexpr const int NR_SIZE_FOR = 9;
}

UlaModel* UlaService::process( const BinaryRowModel* binary ) const {

    if( LabelManager::instance().isLabelSkip() ){
        return nullptr;
    }

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
        case TipoOperacaoAssemblyEnum::MUL:
            resultOperation = mul( values.first(), values.last() );
            break;
        case TipoOperacaoAssemblyEnum::DIV:
            resultOperation = div( values.first(), values.last() );
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
        { "01101", TipoOperacaoAssemblyEnum::MUL },
        { "01110", TipoOperacaoAssemblyEnum::DIV },
    };

    return dsOperacaoByTp.value( dsUpcode, TipoOperacaoAssemblyEnum::UNDEFINED );
}

QString UlaService::sum( const QString& first, const QString& second ) const {

    qDebug() << " UlaService::sum [FIRST]" << first << "[SECOND]" << second;

    LogUlaManager* logUlaManager = &LogUlaManager::instance();

    int nrFirst = first.toInt();
    int nrSecond = second.toInt();

    int rest = 0;
    QString sum = "";    

    logUlaManager->addRow( "SUM INIT" );

    logUlaManager->addRow( QString( "VALUES: %0 | %1" ).arg( first, second ) );

    while( nrFirst != 0 || nrSecond != 0 )  {

        const int lastNumberFirst = ( nrFirst % NR_SIZE_INT );
        const int lastNumberSecond = ( nrSecond % NR_SIZE_INT );

        sum.prepend( QString::number( ( lastNumberFirst + lastNumberSecond + rest ) % NR_BASE_BINARY )[0] );

        logUlaManager->addRow( QString( "%0 + %1 + %2 % %3 = %4").arg( QString::number( lastNumberFirst ), QString::number( lastNumberSecond), QString::number( rest ), QString::number( NR_BASE_BINARY ), sum.at(0) ) );

        rest = (int)( ( lastNumberFirst + lastNumberSecond + rest ) / NR_BASE_BINARY );

        logUlaManager->addRow( QString( "%0 + %1 + %2 / %3 = %4").arg( QString::number( lastNumberFirst ), QString::number( lastNumberSecond), QString::number( rest ), QString::number( NR_BASE_BINARY ),  QString::number( rest ) ) );

        nrFirst /= NR_SIZE_INT;
        nrSecond /= NR_SIZE_INT;

    }

    if ( rest != 0 ) {
        sum.prepend( QString::number( rest )[0] ) ;
    }

    logUlaManager->addRow( "RESULT:" + sum );
    logUlaManager->addRow( "SUM END\n" );

    return sum;
}

QString UlaService::sub( const QString &first, const QString &second ) const {

    QString result = "";
    bool inverter = false;

    LogUlaManager* logUlaManager = &LogUlaManager::instance();

    logUlaManager->addRow( "SUB INIT" );

    for(int index = NR_SIZE_FOR; index >= 0; index--) {
        if(first[index] == second[index]) {

            result.append((!inverter) ? "0" : "1");

            continue;
        }

        if(first[index] > second[index]) {

            result.append((!inverter) ? "1" : "0");

            inverter = false;

            continue;
        }

        if(!inverter) {
            inverter = true;
            result.append("1");
        } else {
            result.append("0");
        }
    }

    std::reverse(result.begin(), result.end());

    logUlaManager->addRow( "RESULT:" + result );
    logUlaManager->addRow( "SUB END\n" );

    return result;

}

QString UlaService::bge( const QString &first, const QString&second ) const {

    QString result = "";

    LogUlaManager* logUlaManager = &LogUlaManager::instance();

    logUlaManager->addRow( "BGE INIT" );

    for( int index = 0; index <= NR_SIZE_FOR; index++ ){

        logUlaManager->addRow( QString( "%0 > %2").arg( first[index], second[index] ) );

        if( first[index] > second[index] ) {
            result = "1";
            break;
        }

        logUlaManager->addRow( QString( "%0 < %2").arg( first[index], second[index] ) );

        if( first[index] < second[index] ){
            result = "0";
            break;
        }
    }

    logUlaManager->addRow( "RESULT: " + result );
    logUlaManager->addRow( "BGE END\n" );

    return result == "" ? "1" : result;
}

QString UlaService::ble(const QString &first, const QString &second) const {

    QString result = "";

    LogUlaManager* logUlaManager = &LogUlaManager::instance();

    logUlaManager->addRow( "BLE INIT" );

    for(int index = 0; index <= NR_SIZE_FOR; index++ ){

        if( first[index] < second[index] ) {
            result = "1";
            break;
        }

        if( first[index] > second[index] ){
            result = "0";
            break;
        }

    }

    logUlaManager->addRow( first + (result == "1" ? " < " : (result == "0" ? " > " : " == ")) + second );
    logUlaManager->addRow( "RESULT:" + result );
    logUlaManager->addRow( "BLE END\n" );

    return result == "" ? "1" : result;
}

QString UlaService::beq(const QString &first, const QString &second) const {

    QString result = "1";

    LogUlaManager* logUlaManager = &LogUlaManager::instance();

    logUlaManager->addRow( "BEQ INIT" );

    for(int index = NR_SIZE_FOR; index >= 0; index--){
        if(first[index] != second[index]) {
            logUlaManager->addRow( QString(first[index]) + " != " + second[index] );
            result = "0";
            break;
        }
    }

    logUlaManager->addRow( first + (result == "1" ? " == " : " != ") + second );
    logUlaManager->addRow( "RESULT:" + result );
    logUlaManager->addRow( "BEQ END\n" );

    return result;
}

QString UlaService::bgt(const QString &first, const QString &second) const {

    QString result = "";

    LogUlaManager* logUlaManager = &LogUlaManager::instance();

    logUlaManager->addRow( "BGT INIT" );

    for( int index = 0; index <= NR_SIZE_FOR; index++ ){

        if( first[index] > second[index] ) {
            result = "1";
            break;
        }

        if( first[index] < second[index] ){
            result = "0";
            break;
        }
    }

    logUlaManager->addRow( first + (result == "1" ? " > " : (result == "0" ? " < " : " == ")) + second );
    logUlaManager->addRow( "RESULT:" + result );
    logUlaManager->addRow( "BGT END\n" );

    return result == "" ? "0" : result;
}

QString UlaService::blt(const QString &first, const QString &second) const {

    QString result = "";

    LogUlaManager* logUlaManager = &LogUlaManager::instance();

    logUlaManager->addRow( "BLT INIT" );

    for( int index = 0; index <= NR_SIZE_FOR; index++ ){

        if( first[index] < second[index] ) {
            result = "1";
            break;
        }

        if( first[index] > second[index] ){
            logUlaManager->addRow( QString(first[index]) + " > " + second[index] );
            result = "0";
            break;
        }
    }

    logUlaManager->addRow( first + (result == "1" ? " < " : (result == "0" ? " > " : " == ")) + second );
    logUlaManager->addRow( "RESULT:" + result );
    logUlaManager->addRow( "BLT END\n" );

    return result == "" ? "0" : result;
}

QString UlaService::bne( const QString &first, const QString &second ) const {

    QString result = "0";

    LogUlaManager* logUlaManager = &LogUlaManager::instance();

    logUlaManager->addRow( "BNE INIT" );

    for(int index = NR_SIZE_FOR; index >= 0; index--){
        if(first[index] != second[index]) {
            result = "1";
            break;
        }
    }

    logUlaManager->addRow( first + (result == "1" ? " != " : " == ") + second );
    logUlaManager->addRow( "RESULT:" + result );
    logUlaManager->addRow( "BNE END\n" );

    return result;
}

QString UlaService::mul( const QString &first, const QString &second ) const {

    long binary1 = first.toLong();
    long binary2 = second.toLong();
    long multiply = 0;
    int digit = 0;
    long factor = 1;

    while ( binary2 != 0 ) {

        digit =  binary2 % NR_SIZE_INT;

        if ( digit == 1 )  {
            binary1 = binary1 * factor;
            multiply = sum( QString::number( binary1 ), QString::number( multiply ) ).toLong();
        } else {
            binary1 = binary1 * factor;
        }

        binary2 = binary2 / NR_SIZE_INT;
        factor = NR_SIZE_INT;

    }

    return QString::number( multiply );

}

QString UlaService::div( const QString &first, const QString& second ) const {

   QString secondModified;
   QString umBinario = "0000000001";
   QString zeroBinario = "0000000000";
   QString resultado = first;
   QString valor;

   QString quociente = zeroBinario;

   for( int index = 0; index <= NR_SIZE_FOR; index++ ){
        if( second[index] == "0" ) {
            secondModified[index] = '1';
        } else {
            secondModified[index] = '0';
        }
    }

    valor = sum( secondModified, umBinario );

    while( resultado != zeroBinario ) {
        resultado = sum( resultado, valor );
        resultado.remove( 0, 1 );
        quociente = sum( quociente, umBinario );
    }

    return quociente;

}
