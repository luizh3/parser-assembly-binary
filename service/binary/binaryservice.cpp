#include "binaryservice.h"

#include <service/memorymanager.h>
#include <service/variable/variablemanager.h>
#include <service/label/labelmanager.h>

namespace {
    constexpr const int NR_SIZE_INT = 10;
}

BinaryRowModel* BinaryService::fromAssemblyToBinary( const AssemblyRowModel* assemblyRow ) const {

    if( LabelManager::instance().isLabelSkip() ){
        return nullptr;
    }

    VariableManager* variableManager = &VariableManager::instance();
    BinaryRowModel* binaryRow = new BinaryRowModel();

    QString rowBinary = "%0 %1";
    QList<QString> valuesStore = {};

    binaryRow->setDsUpcode( tpOperacaoToUpcode( assemblyRow->typeOperation() ) );

    for( const QString& currentValue : assemblyRow->values() ){

        if( variableManager->registersVariables().contains( currentValue ) ){

            const VariableModel* variable = variableManager->getByRegisterName( currentValue );

            switch( assemblyRow->typeOperation() ){
                case TipoOperacaoAssemblyEnum::LOAD:
                case TipoOperacaoAssemblyEnum::MOV:
                    valuesStore.prepend( variable->getRegister()->binaryMemory() );
                    break;
                default:
                    valuesStore.append( toBinary( variable->value() ) );
                    break;
            }

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
        { TipoOperacaoAssemblyEnum::LOAD,"00001" },
        { TipoOperacaoAssemblyEnum::ADD, "00010" },
        { TipoOperacaoAssemblyEnum::SUB, "00011" },
        { TipoOperacaoAssemblyEnum::BGE, "00100" },
        { TipoOperacaoAssemblyEnum::BLE, "00101" },
        { TipoOperacaoAssemblyEnum::BEQ, "00110" },
        { TipoOperacaoAssemblyEnum::BGT, "00111" },
        { TipoOperacaoAssemblyEnum::BLT, "01000" },
        { TipoOperacaoAssemblyEnum::BNE, "01001" },
        { TipoOperacaoAssemblyEnum::JUMP, "01010" },
        { TipoOperacaoAssemblyEnum::LABEL, "01011" },
        { TipoOperacaoAssemblyEnum::MOV, "01100" },
        { TipoOperacaoAssemblyEnum::MUL,"01101" },
        { TipoOperacaoAssemblyEnum::DIV, "01110" },
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


