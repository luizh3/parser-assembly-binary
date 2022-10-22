#include "inputcodeservice.h"

#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QCoreApplication>

#include <service/helper/utilshelper.h>

void InputCodeService::writeText( const QString& text ) const {

    const QString path = UtilsHelper::toAbsolutePath( { DS_DIRECTORY_FILE, DS_FILE_C } );

    QFile file( path );
    if(!file.open( QIODevice::WriteOnly | QIODevice::Text )) {
        qCritical() << "InputCodeController::getInitTex falha ao abrir arquivo";
    }

    // Clear text from file
    file.resize( 0 );

    QTextStream in(&file);

    in << text;

    file.close();

}

QString InputCodeService::readText() const {

    const QString path = UtilsHelper::toAbsolutePath( { DS_DIRECTORY_FILE, DS_FILE_C } );

    QFile file( path );
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "InputCodeController::getInitTex falha ao abrir arquivo";
        return "";
    }

    QString resultText = "";

    QTextStream in(&file);
    while( !in.atEnd() ) {
        resultText.append( in.readLine() );
        resultText.append( "\n" );
    }

    file.close();

    return resultText;

}

constexpr const char* InputCodeService::DS_DIRECTORY_FILE;
constexpr const char* InputCodeService::DS_EXEC_FILE;
constexpr const char* InputCodeService::DS_FILE_C;
