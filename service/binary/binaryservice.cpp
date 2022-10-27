#include "binaryservice.h"

#include <service/memorymanager.h>
#include <service/ula/ulaservice.h>
#include <service/variable/variablemanager.h>


namespace {
    constexpr const int NR_SIZE_INT = 10;
}

BinaryRowModel* BinaryService::fromAssemblyToBinary( const AssemblyRowModel* assemblyRow ) const {

    VariableManager* variableManager = &VariableManager::instance();

    BinaryRowModel* binaryRow = new BinaryRowModel();

    QString rowBinary = "%0 %1";
    QList<QString> valuesStore = {};

    binaryRow->setDsUpcode( tpOperacaoToUpcode( assemblyRow->typeOperation() ) );

    for( const QString& currentValue : assemblyRow->values() ){

        if( variableManager->registersVariables().contains( currentValue ) ){
            const VariableModel* variable = variableManager->getByRegisterName( currentValue );
            valuesStore.append( toBinary( variable->value() ) );
            continue;
        }

        valuesStore.append( toBinary( currentValue.toInt() ) );

    }

    const QString address = MemoryManager::instance().allocValues( valuesStore );

    binaryRow->setAddressMemoryValues( address );
    binaryRow->setRawRow( rowBinary.arg( binaryRow->dsUpcode(), address ) );

    return binaryRow;

}

QString BinaryService::tpOperacaoToUpcode( const TipoOperacaoAssemblyEnum& tpOperacao ) const {

    const QMap<TipoOperacaoAssemblyEnum, QString> dsOperacaoByTp = {
        { TipoOperacaoAssemblyEnum::ADD, "00001" },
        { TipoOperacaoAssemblyEnum::LOAD, "00002" },
        { TipoOperacaoAssemblyEnum::SUB, "00003" },
    };

    return dsOperacaoByTp.value( tpOperacao, "" );
}

QString BinaryService::toBinary( unsigned int number ) const {

    QString binary = "";

    while( number != 0 ){
        binary.prepend( QString::number( number % 2 ) );
        number /= 2;
    }

    return binary;

}

int BinaryService::fromBinary( const QString& binary ) const {

    int nrBinary = binary.toInt();
    int nrResult = 0;
    int base = 1;

    while( nrBinary ) {

        int last_digit = nrBinary % NR_SIZE_INT;
        nrBinary = nrBinary / NR_SIZE_INT;

        nrResult += last_digit * base;

        base *= 2;
    }

    return nrResult;
}


