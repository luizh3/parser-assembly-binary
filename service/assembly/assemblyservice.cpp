#include "assemblyservice.h"

#include <model/variable/conditionmodel.h>

#include <service/memorymanager.h>
#include <service/register/registermanager.h>
#include <service/variable/variablemanager.h>

QList<AssemblyRowModel*> AssemblyService::fromVariablesToAssemblyRow( const QList<QString>& keyVariablesName, const bool inputLabelsVariables ) const {

    QString rawRowAssembly = "";
    QList<AssemblyRowModel*> rowsAssembly = {};
    RegisterManager* registerManager = &RegisterManager::instance();

    for( const QString& key : keyVariablesName ){

        VariableModel* current = VariableManager::instance().get( key );

        if( !inputLabelsVariables && current->isLabel() ){
            continue;
        }

        switch( current->tpOperation() ){
            case TipoOperacaoAssemblyEnum::ADD: {
                current->setRegister( registerManager->getOne() );
                const QList<QString> params = toAsmInstruction( current->paramsWithoutOperators() );
                rawRowAssembly = QString( "ADD %0, [%1], [%2]").arg( current->getRegister()->nameRegister(), params.first(), params.last() );

                AssemblyRowModel* assemblyRow = toAssemblyRow( rawRowAssembly, params, current->tpOperation() );
                assemblyRow->setVariableResultOperation( current );

                rowsAssembly.append( assemblyRow );

                break;
            }
            case TipoOperacaoAssemblyEnum::SUB: {
                current->setRegister( registerManager->getOne() );
                const QList<QString> params = toAsmInstruction( current->paramsWithoutOperators() );
                rawRowAssembly = QString( "SUB %0, [%1], [%2]").arg( current->getRegister()->nameRegister(), params.first(), params.last() );

                AssemblyRowModel* assemblyRow = toAssemblyRow( rawRowAssembly, params, current->tpOperation() );
                assemblyRow->setVariableResultOperation( current );

                rowsAssembly.append( assemblyRow );

                break;
            }
            case TipoOperacaoAssemblyEnum::LOAD: {
                current->setRegister( registerManager->getOne() );
                rawRowAssembly = QString( "LDR %0, %1").arg( current->getRegister()->nameRegister(), current->paramsWithoutOperators().join("") );

                const QString value = current->paramsWithoutOperators().join("");
                current->setValue( value.toInt() );

                AssemblyRowModel* assemblyRow = toAssemblyRow( rawRowAssembly, { value }, current->tpOperation() );
                rowsAssembly.append( assemblyRow );

                break;
            }
            case TipoOperacaoAssemblyEnum::BGE:
                rowsAssembly.append( bge( current ) );
                break;
            default: {
                 break;
            }
        }
    }

   return rowsAssembly;

}

QList<QString> AssemblyService::toAsmInstruction( const QList<QString> &params ) const {

    QList<QString> values = {};

    const VariableManager* variableManager = &VariableManager::instance();

    for( const QString& param : params ){

       if( variableManager->getAllKeys().contains( param ) ){
           values.append( variableManager->get( param )->getRegister()->nameRegister() );
           continue;
       }

       values.append( param );
    }

    return values;
}

AssemblyRowModel* AssemblyService::toAssemblyRow( const QString& rawRow, const QList<QString>& values, const TipoOperacaoAssemblyEnum& tpOperation ) const{

    AssemblyRowModel* assemblyRow = new AssemblyRowModel();

    assemblyRow->setRawTextRow( rawRow );
    assemblyRow->setAddressMemoryRow( MemoryManager::instance().alloc() );
    assemblyRow->setValues( values );
    assemblyRow->setTypeOperation( tpOperation );

    return assemblyRow;


}

QList<AssemblyRowModel*> AssemblyService::bge( VariableModel *variable ) const {

    QList<AssemblyRowModel*> rowsResult = {};

   ConditionModel* condition = static_cast<ConditionModel*>( variable );

   const QList<QString> params = toAsmInstruction( condition->paramsWithoutOperators() );

   const QString rowBge = QString( "%0 %1, %2" ).arg( "BGE", params.first(), params.last() );
   rowsResult.append( toAssemblyRow( rowBge, params, condition->tpOperation() ) );

   const QString jumpRow = QString( "%0 %1" ).arg( "JMP", ".L1" );
   rowsResult.append( toAssemblyRow( jumpRow, {},  TipoOperacaoAssemblyEnum::JUMP ) );

   QList<AssemblyRowModel*> elseVariables = fromVariablesToAssemblyRow( condition->variablesElseContent().keys(), true );
   rowsResult.append( elseVariables );

   const QString labelRow = QString( "%0" ).arg( ".L1" );
   rowsResult.append( toAssemblyRow( labelRow, {},  TipoOperacaoAssemblyEnum::LABEL ) );

   QList<AssemblyRowModel*> ifVariables = fromVariablesToAssemblyRow( condition->variablesIfContent().keys(), true );
   rowsResult.append( ifVariables );

   return rowsResult;
}
