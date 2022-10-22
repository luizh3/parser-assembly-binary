#include "inputcodecontroller.h"

#include <QDebug>
#include <QtConcurrent>

#include <model/resultmodel.h>

#include <service/inputcodeservice.h>
#include <service/helper/utilshelper.h>
#include <service/exception/serviceexception.h>

void InputCodeController::writeText(const QString& text) const {
    return InputCodeService().writeText( text );
}

QString InputCodeController::readText() const {
    return InputCodeService().readText();
}

void InputCodeController::onRunCode() const {

    qInfo() << "InputCodeController::onRunCode";

    const bool isRunCode = UtilsHelper::readValue( UtilsHelper::FG_RUN_CODE ).toBool();

    if( !isRunCode ){
        qInfo() << "InputCodeController::onRunCode [IS_RUN_CODE]" << isRunCode << "O codigo nao sera executado.";
        return;
    }

    ResultModel result;

    runSync( [&](){
        try {
            buildCode();
            execCode();
        }  catch ( const ServiceException& e ) {
            result.setTitle( e.what() );
            result.setMessage( e.value() );
            result.setIsError( true );
        }
    });

    if( result.isError() ){
        emit showMessage( MessageTypeEnum::ERROR, result.title(), result.message() );
    }

    qInfo() << "InputCodeController::onRunCode";

}

void InputCodeController::runSync(const std::function<void ()> &function) const {

    QEventLoop eventLoop;
    QFutureWatcher<void> future;

    QObject::connect( &future, &QFutureWatcher<void>::finished, &eventLoop, &QEventLoop::quit );

    future.setFuture( QtConcurrent::run( function ) );
    eventLoop.exec();

}

QByteArray InputCodeController::execCode() const {

    QString path = UtilsHelper::toAbsolutePath( { InputCodeService::DS_DIRECTORY_FILE } );
    QString execPath = UtilsHelper::toAbsolutePath( { InputCodeService::DS_DIRECTORY_FILE, InputCodeService::DS_EXEC_FILE } );

    QByteArray result = {};

    execProcess( path, execPath, [&result]( const QByteArray& value ){
        qDebug() << "InputCodeController::execCode [VALUE]" << value;
        result = value;
    } );

    return result;
}

void InputCodeController::buildCode() const {

    QString path = UtilsHelper::toAbsolutePath( { InputCodeService::DS_DIRECTORY_FILE } );
    QString buildComand = QString( "gcc -o \"%0\" %1 ").arg( InputCodeService::DS_EXEC_FILE, InputCodeService::DS_FILE_C );

    execProcess( path, buildComand, []( const QByteArray /*value*/ ){
        qDebug() << "InputCodeController::buildCode não implementado";
    } );

}

void InputCodeController::execProcess( const QString& path, const QString& executable, std::function<void (const QByteArray& value )> readFunction ) const {

    QProcess* process = new QProcess();

    QObject::connect(process, &QProcess::readyReadStandardOutput, [process, readFunction]() {
        readFunction( process->readAllStandardOutput() );
    });

    QObject::connect(process, &QProcess::readyReadStandardError, [process]() {
        const QByteArray errorText = process->readAllStandardError();
        qDebug() << " InputCodeController::execProcess [DS_ERROR_TEXT]" << errorText;
        throw ServiceException( "Compilation error!", "falha ao executar o codigo" );
    });

    process->setWorkingDirectory( path );
    process->start( executable );

    process->waitForReadyRead();
    process->close();

    delete process;
}
