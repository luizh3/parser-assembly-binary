#include "binaryservice.h"

#include <service/memorymanager.h>
#include <service/variable/variablemanager.h>

QList<BinaryRowModel*> BinaryService::fromAssemblyToBinary( const QList<AssemblyRowModel*>& assemblyRows ) const {

    QList<BinaryRowModel*> binaryRows = {};

    VariableManager* variableManager = &VariableManager::instance();

    for( AssemblyRowModel* currentRow : assemblyRows ){

        BinaryRowModel* binaryRow = new BinaryRowModel();

        QString rowBinary = "%0 %1";
        QList<QString> valuesStore = {};

        binaryRow->setDsUpcode( tpOperacaoToUpcode( currentRow->typeOperation() ) );

        for( const QString& currentValue : currentRow->values() ){

             if( variableManager->registersVariables().contains( currentValue ) ){
                const VariableModel* variable = variableManager->getByRegisterName( currentValue );
                valuesStore.append( QString().setNum( variable->value(), 2 ) );
                continue;
             }

             valuesStore.append( QString().setNum( currentValue.toInt(), 2 ) );

         }

         const QString address = MemoryManager::instance().allocValues( valuesStore );

         binaryRow->setAddressMemoryValues( address );
         binaryRow->setDrawRow( rowBinary.arg( binaryRow->dsUpcode(), address ) );
         binaryRows.append( binaryRow );

    }

    return binaryRows;

}

QString BinaryService::tpOperacaoToUpcode( const TipoOperacaoAssemblyEnum& tpOperacao ) const {

    const QMap<TipoOperacaoAssemblyEnum, QString> dsOperacaoByTp = {
        { TipoOperacaoAssemblyEnum::ADD, "00001" },
        { TipoOperacaoAssemblyEnum::LOAD, "00002" },
        { TipoOperacaoAssemblyEnum::SUB, "00003" },
    };

    return dsOperacaoByTp.value( tpOperacao, "" );
}

