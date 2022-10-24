#include "binaryservice.h"

#include <service/memorymanager.h>
#include <service/variable/variablemanager.h>

QList<QString> BinaryService::fromAssemblyToBinary( const QList<AssemblyRowModel*>& assemblyRows ) const {

    QList<QString> binaryRows = {};

    VariableManager* variableManager = &VariableManager::instance();

    for( AssemblyRowModel* currentRow : assemblyRows ){

        QString rowBinary = "%0 %1";
        QList<QString> valuesStore = {};

        QString codeOperation = tpOperacaoToUpcode( currentRow->typeOperation() );

         for( const QString& currentValue : currentRow->values() ){

             if( variableManager->getAllKeys().contains( currentValue ) ){
                   VariableModel* variable = variableManager->get( currentValue );
                   valuesStore.append( QString().setNum( variable->value(), 2 ) );
                   continue;
             }

             valuesStore.append( QString().setNum( currentValue.toInt(), 2 ) );

         }

         QString address = MemoryManager::instance().allocValues( valuesStore );

         rowBinary = rowBinary.arg( codeOperation, address );

         binaryRows.append( rowBinary );

    }

    return binaryRows;

}

QString BinaryService::tpOperacaoToUpcode( const TipoOperacaoAssemblyEnum &tpOperacao ) const {

    switch( tpOperacao ){
       case TipoOperacaoAssemblyEnum::ADD:
           return "00001";
       case TipoOperacaoAssemblyEnum::LOAD:
           return "00002";
        case TipoOperacaoAssemblyEnum::SUB:
           return "00003";
        default:
            break;
    }

    return "";

}

