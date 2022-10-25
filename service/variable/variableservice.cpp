#include "variableservice.h"

#include <model/helper/instructionhelper.h>

#include "variablemanager.h"

void VariableService::fromTextToVariables( QString text ) const {

    VariableManager* instance = &VariableManager::instance();

    while( !text.isEmpty() ){

        QString currentText = text.left( text.indexOf(";") );
        text.remove( 0, currentText.size() + 1 );
        currentText = currentText.trimmed();

        QList<QString> valuesRow = currentText.split( ' ' );

        VariableModel* variable = nullptr;

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
