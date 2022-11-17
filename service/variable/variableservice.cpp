#include "variableservice.h"

#include <model/helper/instructionhelper.h>

#include "variablemanager.h"

QMap<QString,VariableModel*> VariableService::fromTextToVariables( QString& text, const bool isLabel ) const {

    QString currentText = text.left( text.indexOf(";") );

        if( currentText.contains( "if" ) ){
            ConditionModel* condition = onIf( text );

//            condition->setVariablesElseContent( fromTextToVariables( condition->rawElseContent(), true ) );
//            condition->setVariablesIfContent( fromTextToVariables( condition->rawIfContent(), true ) );

            VariableManager::instance().add( "CONDITION", condition );

            return { { "CONDITION", condition } };
        }

    text.remove( 0, currentText.size() + 1 );
    currentText = currentText.trimmed();

    QList<QString> valuesRow = currentText.split( ' ' );

    return rowValuesToVariable( valuesRow, isLabel );
}

ConditionModel* VariableService::onIf( QString& text ) const {

    // TODO this routine got really bad, review when have time

    ConditionModel* condition = new ConditionModel();

    const int nrSizeElse = 4;
    const int nrRedundantIndex = 1;

    int indexStartConditionIf = text.indexOf( "(");
    text.remove( 0, indexStartConditionIf + nrRedundantIndex );
    int indexEndConditionIf = text.indexOf( ")");

    const QString dsConditionIf = text.left( indexEndConditionIf );

    QList<QString> params = dsConditionIf.trimmed().split( ' ' );
    for( const QString& current : qAsConst( params ) ){
        if( current.isEmpty() ){
            params.removeAll( current );
        }
    }

    condition->addParam( params );

    text.remove( 0, indexEndConditionIf + nrRedundantIndex );

    const QString dsIfContent = text.mid( text.indexOf("{") + nrRedundantIndex, text.indexOf("}") - nrRedundantIndex ).trimmed();
    condition->setRawIfContent( dsIfContent );

    text.remove( 0, text.indexOf("}") + nrRedundantIndex );

    const bool hasElse = QString( text ).trimmed().leftRef( nrSizeElse ).contains("else");

    if( hasElse ){
        text.remove( 0, text.indexOf("{") + nrRedundantIndex );
        const QString dsElseContent = text.mid( text.indexOf("{") + nrRedundantIndex, text.indexOf("}") - nrRedundantIndex ).trimmed();
        text.remove( 0, text.indexOf("}") + nrRedundantIndex );
        condition->setRawElseContent( dsElseContent );
    }

    return condition;

}

QMap<QString,VariableModel*> VariableService::rowValuesToVariable( QList<QString>& valuesRow, const bool isLabel ) const {

    VariableModel* variable = nullptr;
    QMap<QString,VariableModel*> variables = {};
    VariableManager* variableManager = &VariableManager::instance();

    while( !valuesRow.isEmpty() ){

        if( !variable ){
            variable = new VariableModel();
            variable->setIsLabel( isLabel );
        }

        const QString currentValue = valuesRow.first();
        valuesRow.removeFirst();

        if( InstructionHelper::allTypes().contains( currentValue ) ){
            variable->setType( currentValue );
            continue;
        }

        if( InstructionHelper::allOperators().contains( currentValue ) ){
            variable->addParam( currentValue );
            continue;
        }

        if( InstructionHelper::regexNameVariable().match( currentValue ).hasMatch() ){

            if( hasVariable( currentValue ) && variable->type().trimmed().isEmpty() ){
                delete variable;
                variable = variableManager->get( currentValue );
                variable->clearParams();
                variables.insert( currentValue, variable );
                continue;
            }

            if( hasVariable( currentValue ) ){
                variable->addParam( currentValue );
                continue;
            }

            variables.insert( currentValue, variable );
            variableManager->add( currentValue, variable );
            continue;
        }

        variable->addParam( currentValue );
    }

    return variables;
}

bool VariableService::hasVariable( const QString& dsVariable ) const {
    return VariableManager::instance().getAllKeys().contains( dsVariable );
}
