#include "assemblyservice.h"

#include <model/variable/variablemodel.h>

#include <service/memorymanager.h>
#include <service/register/registermanager.h>
#include <service/variable/variablemanager.h>


QList<AssemblyRowModel*> AssemblyService::fromVariablesToAssemblyRow() const {

    QString drawRowAssembly = "";
    QList<AssemblyRowModel*> rowsAssembly = {};
    RegisterManager* registerManager = &RegisterManager::instance();

    const QList<QString> keyVariablesName = VariableManager::instance().getAllKeys();

    for( const QString& key : keyVariablesName ){

        VariableModel* current = VariableManager::instance().get( key );

        switch( current->tpOperation() ){
            case TipoOperacaoAssemblyEnum::ADD: {
                current->setRegisterName( registerManager->getOne() );
                const QList<QString> params = toAsmInstruction( current->paramsWithoutOperators() );
                drawRowAssembly = QString( "ADD %0, [%1], [%2]").arg( current->registerName(), params.first(), params.last() );

                AssemblyRowModel* assemblyRow = toAssemblyRow( drawRowAssembly, { params.first(), params.last() }, current->tpOperation() );
                rowsAssembly.append( assemblyRow );

                break;
            }
            case TipoOperacaoAssemblyEnum::SUB: {
                current->setRegisterName( registerManager->getOne() );
                const QList<QString> params = toAsmInstruction( current->paramsWithoutOperators() );
                drawRowAssembly = QString( "SUB %0, [%1], [%2]").arg( current->registerName(), params.first(), params.last() );

                AssemblyRowModel* assemblyRow = toAssemblyRow( drawRowAssembly, { params.first(), params.last() }, current->tpOperation() );
                rowsAssembly.append( assemblyRow );

                break;
            }
            case TipoOperacaoAssemblyEnum::LOAD: {
                current->setRegisterName( registerManager->getOne() );
                drawRowAssembly = QString( "LDR %0, %1").arg( current->registerName(), current->paramsWithoutOperators().join("") );

                const QString value = current->paramsWithoutOperators().join("");
                current->setValue( value.toInt() );

                AssemblyRowModel* assemblyRow = toAssemblyRow( drawRowAssembly, { value }, current->tpOperation() );
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
           values.append( instance->get( param )->registerName() );
           continue;
       }

       values.append( param );
    }

    return values;
}

AssemblyRowModel* AssemblyService::toAssemblyRow( const QString &rawRow, const QList<QString>& values, const TipoOperacaoAssemblyEnum& tpOperation ) const{

    AssemblyRowModel* assemblyRow = new AssemblyRowModel();

    assemblyRow->setRawTextRow( rawRow );
    assemblyRow->setAddressMemoryRow( MemoryManager::instance().alloc() );
    assemblyRow->setValues( values );
    assemblyRow->setTypeOperation( tpOperation );

    return assemblyRow;


}
