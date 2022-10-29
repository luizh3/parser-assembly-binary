#include "parserservice.h"

#include <numeric>

#include <service/memorymanager.h>
#include <service/ula/ulaservice.h>
#include <service/binary/binaryservice.h>
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

    VariableService().fromTextToVariables( dsText );

    QList<UlaModel*> operationsUla = {};
    QList<BinaryRowModel*> binaryRows = {};
    QList<AssemblyRowModel*> assemblyRows = AssemblyService().fromVariablesToAssemblyRow();

    for( AssemblyRowModel* assemblyRow : qAsConst( assemblyRows ) ){

       BinaryRowModel* binaryRow = BinaryService().fromAssemblyToBinary( assemblyRow );

       UlaModel* ulaModel = UlaService().process( binaryRow );
       operationsUla.append( ulaModel );

       // TODO maybe to do a method that validated if is expected a result by type operation
       if( assemblyRow->variableResultOperation() ){
           assemblyRow->variableResultOperation()->setValue( BinaryService().fromBinary( ulaModel->result() ) );
       }

       binaryRow->setResultValue( ulaModel->result() );

       binaryRows.append( binaryRow );

    }

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
        dsText.append( QString("%0 %1 %2 %3").arg( row->memoryAddress(), row->values().join(" "), row->result().rightJustified( 10, '0' ) , "\n" ) );
        return dsText;
    });

    return rawText;

}
