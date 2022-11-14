#include "assemblyservice.h"

#include <model/variable/conditionmodel.h>

#include <service/memorymanager.h>
#include <service/label/labelmanager.h>
#include <service/register/registermanager.h>
#include <service/variable/variablemanager.h>

QList<AssemblyRowModel*> AssemblyService::fromVariablesToAssemblyRow( const QList<QString>& keyVariablesName, const bool inputLabelsVariables ) const {

    QList<AssemblyRowModel*> rowsAssembly = {};

    for( const QString& key : keyVariablesName ){

        VariableModel* current = VariableManager::instance().get( key );
        bool isVariableAlreadyAllocated = current->getRegister() != nullptr;

        if( !inputLabelsVariables && current->isLabel() ){
            continue;
        }

        switch( current->tpOperation( isVariableAlreadyAllocated ) ){
            case TipoOperacaoAssemblyEnum::ADD:
                rowsAssembly.append( add( current ) );
                break;
            case TipoOperacaoAssemblyEnum::SUB:
                rowsAssembly.append( sub( current ) );
                break;
            case TipoOperacaoAssemblyEnum::LOAD:
                rowsAssembly.append( load( current ) );
                break;
            case TipoOperacaoAssemblyEnum::MOV:
                rowsAssembly.append( mov( current ) );
                break;
            case TipoOperacaoAssemblyEnum::BGE:
                rowsAssembly.append( bge( current ) );
                break;
            default:
                 break;
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

AssemblyRowModel* AssemblyService::toAssemblyRowByType( const TipoOperacaoAssemblyEnum& tpOperation, const QList<QString>& values ) const {

    QString rawRowAssembly = "";

    switch( tpOperation ){
        case TipoOperacaoAssemblyEnum::JUMP: {
            rawRowAssembly = QString( "JMP .L%0" ).arg( values.first() );
            return toAssemblyRow( rawRowAssembly, values, TipoOperacaoAssemblyEnum::JUMP );
        }
        case TipoOperacaoAssemblyEnum::LABEL: {
             rawRowAssembly = QString( ".L%0" ).arg( values.first() );
            return toAssemblyRow( rawRowAssembly, values, TipoOperacaoAssemblyEnum::LABEL );
        }
        default: {
            break;
        }
    }

    return nullptr;
}

QList<AssemblyRowModel*> AssemblyService::bge( VariableModel *variable ) const {

    QList<AssemblyRowModel*> rowsResult = {};

   ConditionModel* condition = static_cast<ConditionModel*>( variable );

   const QList<QString> params = toAsmInstruction( condition->paramsWithoutOperators() );

   const QString rowBge = QString( "%0 %1, %2" ).arg( "BGE", params.first(), params.last() );
   rowsResult.append( toAssemblyRow( rowBge, params, condition->tpOperation() ) );

   return rowsResult;
}

AssemblyRowModel* AssemblyService::load( VariableModel* variable ) const {

    RegisterManager* registerManager = &RegisterManager::instance();

    variable->setRegister( registerManager->getOne() );
    QString rawRowAssembly = QString( "LDR %0, %1").arg( variable->getRegister()->nameRegister(), variable->paramsWithoutOperators().join("") );

    const QString value = variable->paramsWithoutOperators().join("");
    variable->setValue( value.toInt() );

    return toAssemblyRow( rawRowAssembly, { value }, variable->tpOperation() );

}

AssemblyRowModel *AssemblyService::sub( VariableModel* variable ) const {

    RegisterManager* registerManager = &RegisterManager::instance();

    variable->setRegister( registerManager->getOne() );
    const QList<QString> params = toAsmInstruction( variable->paramsWithoutOperators() );
    QString rawRowAssembly = QString( "SUB %0, [%1], [%2]").arg( variable->getRegister()->nameRegister(), params.first(), params.last() );

    AssemblyRowModel* assemblyRow = toAssemblyRow( rawRowAssembly, params, variable->tpOperation() );
    assemblyRow->setVariableResultOperation( variable );

    return assemblyRow;
}

AssemblyRowModel* AssemblyService::add( VariableModel *variable ) const {

    RegisterManager* registerManager = &RegisterManager::instance();

    variable->setRegister( registerManager->getOne() );
    const QList<QString> params = toAsmInstruction( variable->paramsWithoutOperators() );
    QString rawRowAssembly = QString( "ADD %0, [%1], [%2]").arg( variable->getRegister()->nameRegister(), params.first(), params.last() );

    AssemblyRowModel* assemblyRow = toAssemblyRow( rawRowAssembly, params, variable->tpOperation() );
    assemblyRow->setVariableResultOperation( variable );

    return assemblyRow;
}

QList<AssemblyRowModel*> AssemblyService::mov( VariableModel* variable ) const {

    VariableModel* variableTemporary = new VariableModel( variable );

    AssemblyRowModel* assemblyRowLoad = load( variableTemporary );

    QString rawRowAssembly = QString("MOV [%0], [%1]").arg( variable->getRegister()->nameRegister(), variableTemporary->getRegister()->nameRegister() );

    AssemblyRowModel* assemblyRow = toAssemblyRow( rawRowAssembly, toAsmInstruction( variable->paramsWithoutOperators() ), TipoOperacaoAssemblyEnum::MOV );

    // TODO this is a jerry-rigged, no time now
    if( !LabelManager::instance().hasLabelActive() ){
        variable->setValue( assemblyRowLoad->values().at(0).toInt() );
    }

    RegisterManager::instance().free( variableTemporary->getRegister() );
    delete variableTemporary;

    // TODO clear register, example: mov RA, 0

    return { assemblyRowLoad, assemblyRow };

}
