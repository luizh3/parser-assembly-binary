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
    logUlaManager->addRow( QString( "VALUES: %0 | %1" ).arg( first, second ) );

    for(int index = NR_SIZE_FOR; index >= 0; index--) {
        if(first[index] == second[index]) {

            logUlaManager->addRow( QString( "%0 == %1 = %2").arg( first[index], second[index], (!inverter) ? "0" : "1" ) );

            result.append((!inverter) ? "0" : "1");

            continue;
        }

        if(first[index] > second[index]) {

            logUlaManager->addRow( QString( "%0 > %1 = %2").arg( first[index], second[index], (!inverter) ? "1" : "0" ) );

            result.append((!inverter) ? "1" : "0");

            inverter = false;

            continue;
        }

        if(!inverter) {
            inverter = true;
            result.append("1");
            logUlaManager->addRow( QString( "%0 < %1 = %2").arg( first[index], second[index], "1" ) );

        } else {
            result.append("0");
            logUlaManager->addRow( QString( "%0 < %1 = %2").arg( first[index], second[index], "0" ) );
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
    logUlaManager->addRow( QString( "VALUES: %0 | %1" ).arg( first, second ) );

    for( int index = 0; index <= NR_SIZE_FOR; index++ ){

        logUlaManager->addRow( QString( "%0 > %1").arg( first[index], second[index] ) );

        if( first[index] > second[index] ) {
            result = "1";
            break;
        }

        logUlaManager->addRow( QString( "%0 < %1").arg( first[index], second[index] ) );

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
    logUlaManager->addRow( QString( "VALUES: %0 | %1" ).arg( first, second ) );

    for(int index = 0; index <= NR_SIZE_FOR; index++ ){

        logUlaManager->addRow( QString( "%0 < %1").arg( first[index], second[index] ) );

        if( first[index] < second[index] ) {
            result = "1";
            break;
        }

        logUlaManager->addRow( QString( "%0 > %1").arg( first[index], second[index] ) );

        if( first[index] > second[index] ){
            result = "0";
            break;
        }

    }

    logUlaManager->addRow( "RESULT:" + result );
    logUlaManager->addRow( "BLE END\n" );

    return result == "" ? "1" : result;
}

QString UlaService::beq(const QString &first, const QString &second) const {

    QString result = "1";

    LogUlaManager* logUlaManager = &LogUlaManager::instance();

    logUlaManager->addRow( "BEQ INIT" );
    logUlaManager->addRow( QString( "VALUES: %0 | %1" ).arg( first, second ) );

    for(int index = NR_SIZE_FOR; index >= 0; index--){

        logUlaManager->addRow( QString( "%0 != %1").arg( first[index], second[index] ) );

        if(first[index] != second[index]) {
            result = "0";
            break;
        }
    }

    logUlaManager->addRow( "RESULT:" + result );
    logUlaManager->addRow( "BEQ END\n" );

    return result;
}

QString UlaService::bgt(const QString &first, const QString &second) const {

    QString result = "";

    LogUlaManager* logUlaManager = &LogUlaManager::instance();

    logUlaManager->addRow( "BGT INIT" );
    logUlaManager->addRow( QString( "VALUES: %0 | %1" ).arg( first, second ) );

    for( int index = 0; index <= NR_SIZE_FOR; index++ ){

        logUlaManager->addRow( QString( "%0 > %1").arg( first[index], second[index] ) );

        if( first[index] > second[index] ) {
            result = "1";
            break;
        }

        logUlaManager->addRow( QString( "%0 < %1").arg( first[index], second[index] ) );

        if( first[index] < second[index] ){
            result = "0";
            break;
        }
    }

    logUlaManager->addRow( "RESULT:" + result );
    logUlaManager->addRow( "BGT END\n" );

    return result == "" ? "0" : result;
}

QString UlaService::blt(const QString &first, const QString &second) const {

    QString result = "";

    LogUlaManager* logUlaManager = &LogUlaManager::instance();

    logUlaManager->addRow( "BLT INIT" );
    logUlaManager->addRow( QString( "VALUES: %0 | %1" ).arg( first, second ) );

    for( int index = 0; index <= NR_SIZE_FOR; index++ ){

        logUlaManager->addRow( QString( "%0 < %1").arg( first[index], second[index] ) );

        if( first[index] < second[index] ) {
            result = "1";
            break;
        }

        logUlaManager->addRow( QString( "%0 > %1").arg( first[index], second[index] ) );

        if( first[index] > second[index] ){
            result = "0";
            break;
        }
    }

    logUlaManager->addRow( "RESULT:" + result );
    logUlaManager->addRow( "BLT END\n" );

    return result == "" ? "0" : result;
}

QString UlaService::bne( const QString &first, const QString &second ) const {

    QString result = "0";

    LogUlaManager* logUlaManager = &LogUlaManager::instance();

    logUlaManager->addRow( "BNE INIT" );
    logUlaManager->addRow( QString( "VALUES: %0 | %1" ).arg( first, second ) );

    for( int index = NR_SIZE_FOR; index >= 0; index-- ){

        logUlaManager->addRow( QString( "%0 != %1").arg( first[index], second[index] ) );

        if( first[index] != second[index] ) {
            result = "1";
            break;
        }
    }

    logUlaManager->addRow( "RESULT:" + result );
    logUlaManager->addRow( "BNE END\n" );

    return result;
}

QString UlaService::mul( const QString &first, const QString &second ) const {

    if( first.toInt() <= 0 || second.toInt() <= 0 ) {
        return "0";
    }

    LogUlaManager* logUlaManager = &LogUlaManager::instance();

    long nrFirstBinary = first.toLong();
    long nrSecondBinary = second.toLong();
    long multiply = 0;
    int digit = 0;
    long factor = 1;

    logUlaManager->addRow( "MUL INIT" );
    logUlaManager->addRow( QString( "VALUES: %0 | %1" ).arg( first, second ) );
    logUlaManager->addRow( QString( "WHILE: %0 != 0" ).arg( second ) );

    while ( nrSecondBinary != 0 ) {

        digit = nrSecondBinary % NR_SIZE_INT;

        logUlaManager->addRow( QString( "DIGIT = SECOND(%0) % SIZE_INT(%1)" ).arg( QString::number( nrSecondBinary ), QString::number( NR_SIZE_INT ) ) );
        logUlaManager->addRow( QString( "FIRST = FIRST(%0) * FACTOR(%1)" ).arg( QString::number( nrFirstBinary ), QString::number( factor ) ) );

        nrFirstBinary = nrFirstBinary * factor;

        logUlaManager->addRow( QString( "DIGIT(%0) == 1 \n" ).arg( QString::number( digit ) ) );

        if ( digit == 1 )  {
            multiply = sum( QString::number( nrFirstBinary ), QString::number( multiply ) ).toLong();
        }

        logUlaManager->addRow( QString( "SECOND = SECOND(%0) / SIZE_INT(%1)" ).arg( QString::number( nrSecondBinary ), QString::number( NR_SIZE_INT ) ) );
        logUlaManager->addRow( QString( "FACTOR = %0 \n" ).arg( QString::number( NR_SIZE_INT ) ) );

        nrSecondBinary = nrSecondBinary / NR_SIZE_INT;
        factor = NR_SIZE_INT;


    }

    logUlaManager->addRow( QString("RESULT: %1").arg( QString::number( multiply ) ) );
    logUlaManager->addRow( "MUL END" );

    return QString::number( multiply );

}

QString UlaService::div( const QString &first, const QString& second ) const {

    if( first.toInt() <= 0 || second.toInt() <= 0 ) {
        return "0";
    }

   QString secondModified;
   QString umBinario = "0000000001";
   QString zeroBinario = "0000000000";
   QString resultado = first;
   QString valor;

   QString quociente = zeroBinario;

   LogUlaManager* logUlaManager = &LogUlaManager::instance();

   logUlaManager->addRow( "DIV INIT" );
   logUlaManager->addRow( QString( "VALUES: %0 | %1" ).arg( first, second ) );

   for( int index = 0; index <= NR_SIZE_FOR; index++ ){

        if( second[index] == "0" ) {
            secondModified[index] = '1';
            logUlaManager->addRow( QString( "SECONDMODIFIED = 1"));
        } else {
            secondModified[index] = '0';
            logUlaManager->addRow( QString( "SECONDMODIFIED = 0"));
        }
    }

    valor = sum( secondModified, umBinario );
    logUlaManager->addRow( QString( "VALUE = SECONDMODIFIED(%0) + ONEBINARY(%1)").arg(secondModified, umBinario) );

    logUlaManager->addRow( QString( "WHILE: %0 != %1").arg(resultado, zeroBinario) );
    while( resultado != zeroBinario ) {
        resultado = sum( resultado, valor );
        logUlaManager->addRow( QString( "RESULT = RESULT(%0) + VALUE(%1)").arg(resultado, valor) );
        resultado.remove( 0, 1 );
        logUlaManager->addRow( QString( "REMOVE: FIRST TERM OF (%0").arg(resultado));
        quociente = sum( quociente, umBinario );
        logUlaManager->addRow( QString( "QUOCIENT = QUOCIENT(%0) +  ONEBINARY(%1)").arg(quociente, umBinario) );
    }

    logUlaManager->addRow( QString( "QUOCIENT: %0").arg(quociente) );
    logUlaManager->addRow( QString( "DIV END"));
    return quociente;

}
