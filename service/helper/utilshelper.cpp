#include "utilshelper.h"

#include <QDir>
#include <QDebug>
#include <QSettings>
#include <QCoreApplication>

namespace {
    constexpr const char* DS_BIND_VALUE_PATH = "%0/%1";
    constexpr const char* DS_PATH_FILE = "config/configs.ini";
}

QString UtilsHelper::absolutePathApplication() {

   const QList<QString> DIRECTORYS_INVALIDS = {
       "/debug"
   };

   QString path = QDir::fromNativeSeparators( QCoreApplication::applicationDirPath());

    for( const QString& current: DIRECTORYS_INVALIDS ){
        path.replace( current, "" );
    }

    return QDir::toNativeSeparators( path );
}

QString UtilsHelper::toAbsolutePath( const QList<QString>& directorys, const QString& path ) {

    qInfo() << "UtilsHelper::toAbsolutePath [DIRECTORYS]" << directorys << "[PATH]" << path;

    QString currentPath = path;

    for( const QString& directory : directorys ){
        currentPath.append( QString( "/%0" ).arg( directory ) );
    }

    const QString result = QDir::toNativeSeparators( currentPath );

    qInfo() << "UtilsHelper::toAbsolutePath [RETURN]" << result;

    return result;
}

QVariant UtilsHelper::readValue( const QString pathValue ) {

    qInfo() << "UtilsHelper::readConfigs";

    QSettings settings( pathConfigFile(), QSettings::IniFormat);

    const QVariant value = settings.value( QString( DS_BIND_VALUE_PATH ).arg( DS_CONFIGS, pathValue ) );

    qInfo() << "UtilsHelper::readConfigs [VALUE]" << value;

    return value;

}

QString UtilsHelper::pathConfigFile() {
    qInfo() << "UtilsHelper::pathConfigFile";
    QString path = UtilsHelper::toAbsolutePath( { DS_PATH_FILE } );
    qInfo() << "UtilsHelper::pathConfigFile" << path;
    return path;
}

constexpr const char* UtilsHelper::DS_CONFIGS;
constexpr const char* UtilsHelper::FG_RUN_CODE;
