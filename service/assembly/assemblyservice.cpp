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
            case TipoOperacaoAssemblyEnum::BEQ:
                rowsAssembly.append( beq( current ) );
                break;
            case TipoOperacaoAssemblyEnum::BGT:
                rowsAssembly.append( bgt( current ) );
                break;
            case TipoOperacaoAssemblyEnum::BLT:
                rowsAssembly.append( blt( current ) );
                break;
            case TipoOperacaoAssemblyEnum::BNE:
                rowsAssembly.append( bne( current ) );
                break;
            case TipoOperacaoAssemblyEnum::BLE:
                rowsAssembly.append( ble( current ) );
                break;
            case TipoOperacaoAssemblyEnum::MUL:
                rowsAssembly.append( mul( current ) );
                break;
            case TipoOperacaoAssemblyEnum::DIV:
                rowsAssembly.append( div( current ) );
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

QList<AssemblyRowModel*> AssemblyService::numbersToAsmInstruction( QList<QString>& params ) const {

    VariableManager* variableManager = &VariableManager::instance();

    QList<AssemblyRowModel*> assemblyRows = {};

    QList<QString> newParams = {};

    for( int i = 0; i < params.length(); i++ ){

        if( !variableManager->registersVariables().contains( params[i] ) ){

            VariableModel* variable = new VariableModel();
            variable->setTpOperation( TipoOperacaoAssemblyEnum::LOAD );
            variable->addParam( params[i] );

            assemblyRows.append( load(variable) );

            newParams.append( variable->getRegister()->nameRegister() );

            VariableManager::instance().add( variable->getRegister()->nameRegister(), variable );

            continue;

        }

        newParams.append( params[i] );

    }

    params.swap( newParams );

    return assemblyRows;
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
            const QString memory = MemoryManager::instance().allocBinaryMemory();
            LabelManager::instance().addMemoryByLabel( values.first(), memory );
            return toAssemblyRow( rawRowAssembly, { memory }, TipoOperacaoAssemblyEnum::JUMP );
        }
        case TipoOperacaoAssemblyEnum::LABEL: {
             rawRowAssembly = QString( ".L%0" ).arg( values.first() );
             const QString memory = LabelManager::instance().getMemoryByLabel( values.first() );
             return toAssemblyRow( rawRowAssembly, { memory }, TipoOperacaoAssemblyEnum::LABEL );
        }
        default: {
            break;
        }
    }

    return nullptr;
}

QList<AssemblyRowModel*> AssemblyService::bge( const VariableModel* variable ) const {
    return toConditionAssemblyRow( QString( "BGE %1, %2" ), variable );
}

QList<AssemblyRowModel*> AssemblyService::beq( const VariableModel* variable) const {
    return toConditionAssemblyRow( QString( "BEQ %1, %2" ), variable );
}

QList<AssemblyRowModel*> AssemblyService::bgt( const VariableModel* variable) const {
    return toConditionAssemblyRow( QString( "BGT %1, %2" ), variable );
}

QList<AssemblyRowModel*> AssemblyService::blt( const VariableModel* variable) const {
    return toConditionAssemblyRow( QString( "BLT %1, %2" ), variable );
}

QList<AssemblyRowModel*> AssemblyService::bne( const VariableModel* variable) const {
    return toConditionAssemblyRow( QString( "BNE %1, %2" ), variable );
}

QList<AssemblyRowModel*> AssemblyService::ble( const VariableModel* variable) const{
    return toConditionAssemblyRow( QString( "BLE %1, %2" ), variable );
}

QList<AssemblyRowModel*> AssemblyService::toConditionAssemblyRow( const QString& dsRow, const VariableModel *variable ) const {
   const ConditionModel* condition = static_cast<const ConditionModel*>( variable );
   QList<QString> params = toAsmInstruction( condition->paramsWithoutOperators() );
   QList<AssemblyRowModel*> assemblyRows = numbersToAsmInstruction( params );
   const QString dsRowAssembly = QString( dsRow ).arg( params.first(), params.last() );
   assemblyRows.append( toAssemblyRow( dsRowAssembly, params, condition->tpOperation() ) );
   return assemblyRows;
}

QList<AssemblyRowModel *> AssemblyService::toAritmeticAssemblyRow(const QString& dsRow, VariableModel* variable) const {

    RegisterManager* registerManager = &RegisterManager::instance();

    variable->setRegister( registerManager->getOne() );
    QList<QString> params = toAsmInstruction( variable->paramsWithoutOperators() );
    QList<AssemblyRowModel*> assemblyRows = numbersToAsmInstruction( params );
    QString rawRowAssembly = QString( dsRow ).arg( variable->getRegister()->nameRegister(), params.first(), params.last() );

    AssemblyRowModel* assemblyRow = toAssemblyRow( rawRowAssembly, params, variable->tpOperation() );
    assemblyRow->setVariableResultOperation( variable );
    assemblyRows.append( assemblyRow );

    return assemblyRows;

}

AssemblyRowModel* AssemblyService::load( VariableModel* variable ) const {

    VariableManager* variableManager = &VariableManager::instance();

    RegisterManager* registerManager = &RegisterManager::instance();

    variable->setRegister( registerManager->getOne() );

    QString dsValue = variable->paramsWithoutOperators().join("");

    VariableModel* variableCopy = nullptr;

    if( variableManager->getAllKeys().contains( dsValue ) ){
        variableCopy = variableManager->get( dsValue );
    }

    QString dsAssemblyRow = variableCopy ? QString( "LDR %0, [%1]") : QString( "LDR %0, %1");

    QString rawRowAssembly = dsAssemblyRow.arg( variable->getRegister()->nameRegister(), variableCopy ? variableCopy->getRegister()->nameRegister() : dsValue );

    const QString value = variableCopy ? QString::number( variableCopy->value() ) : dsValue;
    variable->setValue( value.toInt() );

    return toAssemblyRow( rawRowAssembly, { variable->getRegister()->nameRegister(), value }, TipoOperacaoAssemblyEnum::LOAD );

}

AssemblyRowModel *AssemblyService::sub( VariableModel* variable ) const {

    // TODO ajustar o sub para ser igual ao add
    RegisterManager* registerManager = &RegisterManager::instance();

    variable->setRegister( registerManager->getOne() );
    const QList<QString> params = toAsmInstruction( variable->paramsWithoutOperators() );
    QString rawRowAssembly = QString( "SUB %0, [%1], [%2]").arg( variable->getRegister()->nameRegister(), params.first(), params.last() );

    AssemblyRowModel* assemblyRow = toAssemblyRow( rawRowAssembly, params, variable->tpOperation() );
    assemblyRow->setVariableResultOperation( variable );

    return assemblyRow;
}

QList<AssemblyRowModel*> AssemblyService::add( VariableModel *variable ) const {

    RegisterManager* registerManager = &RegisterManager::instance();

    variable->setRegister( registerManager->getOne() );
    QList<QString> params = toAsmInstruction( variable->paramsWithoutOperators() );
    QList<AssemblyRowModel*> assemblyRows = numbersToAsmInstruction( params );
    QString rawRowAssembly = QString( "ADD %0, [%1], [%2]").arg( variable->getRegister()->nameRegister(), params.first(), params.last() );

    AssemblyRowModel* assemblyRow = toAssemblyRow( rawRowAssembly, params, variable->tpOperation() );
    assemblyRow->setVariableResultOperation( variable );
    assemblyRows.append( assemblyRow );

    return assemblyRows;
}

QList<AssemblyRowModel*> AssemblyService::mov( VariableModel* variable ) const {

    VariableModel* variableLoad = new VariableModel( variable );

    AssemblyRowModel* assemblyRowLoad = load( variableLoad );

    QString rawRowAssembly = QString("MOV [%0], [%1]").arg( variable->getRegister()->nameRegister(), variableLoad->getRegister()->nameRegister() );

    QList<QString> params = toAsmInstruction( variable->paramsWithoutOperators() );
    params.prepend( variable->getRegister()->nameRegister() );

    AssemblyRowModel* assemblyRow = toAssemblyRow( rawRowAssembly, params, TipoOperacaoAssemblyEnum::MOV );

    // TODO this is a jerry-rigged, no time now
    if( !LabelManager::instance().hasLabelActive() ){
        variable->setValue( assemblyRowLoad->values().last().toInt() );
    }

    VariableManager::instance().add( variableLoad->getRegister()->nameRegister(), variableLoad );

    // TODO clear register, example: mov RA, 0

    return { assemblyRowLoad, assemblyRow };

}

QList<AssemblyRowModel*> AssemblyService::mul( VariableModel* variable ) const {
    return toAritmeticAssemblyRow( "MUL %0, [%1], [%2]", variable );
}

QList<AssemblyRowModel*> AssemblyService::div( VariableModel* variable ) const {
    return toAritmeticAssemblyRow( "DIV %0, [%1], [%2]", variable );
}
