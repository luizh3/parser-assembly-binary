#include "parsercontroller.h"

#include <service/parser/parserservice.h>

void ParserController::makeParser( QString text ) const {
   ParserService().makeParser( text );
}
