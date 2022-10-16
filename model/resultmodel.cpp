#include "resultmodel.h"

ResultModel::ResultModel() :
    _title(""),
    _message(""),
    _isError(false){}

const QString &ResultModel::title() const {
    return _title;
}

void ResultModel::setTitle( const QString &newTitle ) {
    _title = newTitle;
}

const QString &ResultModel::message() const {
    return _message;
}

void ResultModel::setMessage( const QString &newMessage ) {
    _message = newMessage;
}

bool ResultModel::isError() const {
    return _isError;
}

void ResultModel::setIsError( bool newIsError ) {
    _isError = newIsError;
}
