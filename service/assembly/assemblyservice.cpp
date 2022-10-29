#include "assemblyservice.h"

#include <service/memorymanager.h>
#include <service/register/registermanager.h>
#include <service/variable/variablemanager.h>

QList<AssemblyRowModel*> AssemblyService::fromVariablesToAssemblyRow() const {

    QString rawRowAssembly = "";
    QList<AssemblyRowModel*> rowsAssembly = {};
    RegisterManager* registerManager = &RegisterManager::instance();

    const QList<QString> keyVariablesName = VariableManager::instance().getAllKeys();

    for( const QString& key : keyVariablesName ){

        VariableModel* current = VariableManager::instance().get( key );

        switch( current->tpOperation() ){
            case TipoOperacaoAssemblyEnum::ADD: {
                current->setRegister( registerManager->getOne() );
                const QList<QString> params = toAsmInstruction( current->paramsWithoutOperators() );
                rawRowAssembly = QString( "ADD %0, [%1], [%2]").arg( current->getRegister()->nameRegister(), params.first(), params.last() );

                AssemblyRowModel* assemblyRow = toAssemblyRow( rawRowAssembly, { params.first(), params.last() }, current->tpOperation() );
                assemblyRow->setVariableResultOperation( current );

                rowsAssembly.append( assemblyRow );

                break;
            }
            case TipoOperacaoAssemblyEnum::SUB: {
                current->setRegister( registerManager->getOne() );
                const QList<QString> params = toAsmInstruction( current->paramsWithoutOperators() );
                rawRowAssembly = QString( "SUB %0, [%1], [%2]").arg( current->getRegister()->nameRegister(), params.first(), params.last() );

                AssemblyRowModel* assemblyRow = toAssemblyRow( rawRowAssembly, { params.first(), params.last() }, current->tpOperation() );
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
            default: {
                 break;
            }
        }
    }

   return rowsAssembly;

}

QList<QString> AssemblyService::toAsmInstruction( const QList<QString> &params ) const {

    QList<QString> values = {};

    const VariableManager* instance = &VariableManager::instance();

    for( const QString& param : params ){

       if( instance->getAllKeys().contains( param ) ){
           values.append( instance->get( param )->getRegister()->nameRegister() );
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
