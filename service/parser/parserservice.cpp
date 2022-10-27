#include "parserservice.h"

#include <service/ula/ulaservice.h>
#include <service/binary/binaryservice.h>
#include <service/assembly/assemblyservice.h>
#include <service/variable/variableservice.h>

#include <service/memorymanager.h>

void ParserService::formatText( QString &text ) const {

   text.remove( 0, text.indexOf("{") + 1 );
   text = text.trimmed();
   text.remove( text.length() - 1, text.length() );
   text.replace( "\n", "" );

}

void ParserService::makeParser( QString dsText ) const {

    //TODO review all code search for memory leak, probably have a lot
    //TODO review all code for put log in any method

    formatText( dsText );

    VariableService().fromTextToVariables( dsText );

    QList<AssemblyRowModel*> assemblyRows = AssemblyService().fromVariablesToAssemblyRow();

    QList<const BinaryRowModel*> binaryRows = {};

    for( AssemblyRowModel* assemblyRow : qAsConst( assemblyRows ) ){

       const BinaryRowModel* binaryRow = BinaryService().fromAssemblyToBinary( assemblyRow );

       const QString result = UlaService().process( binaryRow );

       // TODO maybe to do a method that validated if is expected a result by type operation
       if( assemblyRow->variableResultOperation() ){
           assemblyRow->variableResultOperation()->setValue( BinaryService().fromBinary( result ) );
       }

       binaryRows.append( binaryRow );

    }

    qDebug() << binaryRows;

}
