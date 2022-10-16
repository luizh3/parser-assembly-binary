#include "serviceexception.h"

ServiceException::ServiceException( const QString& what, const QString& value ) :
 std::runtime_error( what.toStdString() ),
 _value( value ) {}

const QString& ServiceException::value() const {
    return _value;
}

void ServiceException::setValue( const QString &newValue ) {
    _value = newValue;
}
