#include "variableservice.h"

#include <model/helper/instructionhelper.h>

#include "variablemanager.h"

void VariableService::fromTextToVariables( QString text ) const {

    while( !text.isEmpty() ){

        QString currentText = text.left( text.indexOf(";") );
        currentText = currentText.trimmed();
        text.remove( 0, currentText.size() + 1 );

        QList<QString> valuesRow = currentText.split( ' ' );

        VariableModel* variable = nullptr;

        VariableManager* instance = &VariableManager::instance();

        while( !valuesRow.isEmpty() ){

            if( !variable ){
                variable = new VariableModel();
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

                if( instance->getAllKeys().contains( currentValue ) ){
                    variable->addParam( currentValue );
                    continue;
                }

                instance->add( currentValue, variable );
                continue;
            }

            variable->addParam( currentValue );
        }
    }
}
