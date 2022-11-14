#include "parserservice.h"

#include <numeric>

#include <service/memorymanager.h>
#include <service/ula/ulaservice.h>
#include <service/binary/binaryservice.h>
#include <service/label/labelmanager.h>
#include <service/register/registermanager.h>
#include <service/assembly/assemblyservice.h>
#include <service/variable/variableservice.h>
#include <service/variable/variablemanager.h>

void ParserService::formatText( QString &text ) const {

   text.remove( 0, text.indexOf("{") + 1 );
   text = text.trimmed();
   text.remove( text.length() - 1, text.length() );
   text.replace( "\n", "" );

}

ParserResultModel* ParserService::makeParser( QString dsText ) const {

    //TODO review all code search for memory leak, probably have a lot
    //TODO review all code for put log in any method

    formatText( dsText );
    QList<UlaModel*> operationsUla = {};
    QList<AssemblyRowModel*> assemblyRows = {};
    QList<BinaryRowModel*> binaryRows = {};

    toObjectsFromText( dsText, assemblyRows, binaryRows, operationsUla );

    ParserResultModel* parserResult = toParserResult( assemblyRows, binaryRows, operationsUla );

    qDeleteAll( operationsUla );
    qDeleteAll( binaryRows );
    qDeleteAll( assemblyRows );

    VariableManager::instance().reset();
    MemoryManager::instance().reset();
    RegisterManager::instance().reset();

    return parserResult;

}

ParserResultModel *ParserService::toParserResult( const QList<AssemblyRowModel*>& assemblyRows, const QList<BinaryRowModel*>& binaryRows, const QList<UlaModel*>& resultsUla  ) const {

    ParserResultModel* parserResult = new ParserResultModel();
    parserResult->setDsCodeResultAssembly( assemblyRowToRawText( assemblyRows ) );
    parserResult->setDsCodeResultBinary( binaryRowToRawText( binaryRows) );
    parserResult->setDsCodeResultUla( operationsUlaToRawText( resultsUla ) );
    return parserResult;

}


QString ParserService::assemblyRowToRawText( const QList<AssemblyRowModel*>& rows ) const {

    QString rawText = "";

    rawText = std::accumulate( rows.cbegin(), rows.cend(), rawText, []( QString dsText, const AssemblyRowModel* row ){
        dsText.append( QString("%0 %1").arg( row->rawTextRow(), "\n" ) );
        return dsText;
    });

    return rawText;

}

QString ParserService::binaryRowToRawText(const QList<BinaryRowModel*>& rows) const {

    QString rawText = "";

    rawText = std::accumulate( rows.cbegin(), rows.cend(), rawText, []( QString dsText, const BinaryRowModel* row ){
        dsText.append( QString("%0 %1").arg( row->rawRow(), "\n" ) );
        return dsText;
    });

    return rawText;

}

QString ParserService::operationsUlaToRawText( const QList<UlaModel*>& operationsUla ) const {

    QString rawText = "";

    rawText = std::accumulate( operationsUla.cbegin(), operationsUla.cend(), rawText, []( QString dsText, const UlaModel* row ){

        switch( row->tpOperacao() ){
            case TipoOperacaoAssemblyEnum::LOAD:
                dsText.append( QString("%0 %1 %2").arg( row->memoryAddress(), row->values().join(" "), "\n" ) );
                break;
            default:
                dsText.append( QString("%0 %1 %2 %3").arg( row->memoryAddress(), row->values().join(" "), row->result().rightJustified( 10, '0' ) , "\n" ) );
                break;
        }

        return dsText;
    });

    return rawText;

}

void ParserService::toObjectsFromText( QString& dsText, QList<AssemblyRowModel*>& rowsAssembly, QList<BinaryRowModel*>& rowsBinary, QList<UlaModel*>& operationsUla ) const {

    while( !dsText.isEmpty() ) {

        QMap<QString, VariableModel*> variables = VariableService().fromTextToVariables( dsText );

        const QList<AssemblyRowModel*> assemblyResultRows = AssemblyService().fromVariablesToAssemblyRow( variables.keys() );
        rowsAssembly.append( assemblyResultRows );

        for( const AssemblyRowModel* currentRow : qAsConst( assemblyResultRows ) ){

            BinaryRowModel* binaryRow = BinaryService().fromAssemblyToBinary( currentRow );

            if( !binaryRow ){
                continue;
            }

            rowsBinary.append( binaryRow );

            UlaModel* ulaModel = UlaService().process( binaryRow );
            operationsUla.append( ulaModel );

            activeLabel( !ulaModel->result().toInt(), ulaModel->tpOperacao() );

            // TODO maybe to do a method that validated if is expected a result by type operation
            if( currentRow->variableResultOperation() ){
              currentRow->variableResultOperation()->setValue( BinaryService().fromBinary( ulaModel->result() ) );
            }

            binaryRow->setResultValue( ulaModel->result() );

        }

        // TODO this is a jerry-rigged, no time now
        QList<QString> nameVariables = variables.keys();

        for( const QString& key : qAsConst( nameVariables ) ){

            VariableModel* variable = variables.value( key );

            if( variable->tpVariable() == VariableModel::TypeVariableEnum::CONDITION ){

                ConditionModel* condition = static_cast<ConditionModel*>( variable );

                QString rawIfContent = condition->rawIfContent();
                QString rawElseContent = condition->rawElseContent();

                LabelManager* label = &LabelManager::instance();

                QString firstLabel = label->getDsNextLabel();
                QString secondLabel = label->getDsNextLabel();

                // TODO change how this is make

                rowsAssembly.append( AssemblyService().toAssemblyRowByType( TipoOperacaoAssemblyEnum::JUMP, { firstLabel } ) );
                toObjectsFromText( rawIfContent, rowsAssembly, rowsBinary, operationsUla );
                rowsAssembly.append( AssemblyService().toAssemblyRowByType( TipoOperacaoAssemblyEnum::JUMP, { secondLabel } ) );

                label->setTpLabelJump( label->hasLabelActive() ? LabelManager::TypeLabelJumpEnum::NONE : LabelManager::TypeLabelJumpEnum::JUMP );

                rowsAssembly.append( AssemblyService().toAssemblyRowByType( TipoOperacaoAssemblyEnum::LABEL, { firstLabel } ) );
                toObjectsFromText( rawElseContent, rowsAssembly, rowsBinary, operationsUla );

                label->setTpLabelJump( LabelManager::TypeLabelJumpEnum::NONE );
                rowsAssembly.append( AssemblyService().toAssemblyRowByType( TipoOperacaoAssemblyEnum::LABEL, { secondLabel } ) );

            }

        }

    }

}

void ParserService::activeLabel( const bool result, const TipoOperacaoAssemblyEnum& tpLastOperation  ) const {

    LabelManager* label = &LabelManager::instance();

    switch( tpLastOperation ) {
        case TipoOperacaoAssemblyEnum::BEQ:
        case TipoOperacaoAssemblyEnum::BGT:
        case TipoOperacaoAssemblyEnum::BLE:
        case TipoOperacaoAssemblyEnum::BNE:
        case TipoOperacaoAssemblyEnum::BLT:
        case TipoOperacaoAssemblyEnum::BGE:{
            bool isLabel = result;

            if( isLabel ){
                label->setTpLabelJump( LabelManager::TypeLabelJumpEnum::CONDICIONAL );
            }

            break;
        }
        default:
            break;
    }
}
