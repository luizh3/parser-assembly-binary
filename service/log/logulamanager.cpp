#include "logulamanager.h"

LogUlaManager::LogUlaManager() :
    _rows( {} ){}

LogUlaManager& LogUlaManager::instance() {
    static LogUlaManager logUlaManager;
    return logUlaManager;
}

void LogUlaManager::addRow( const QString& row ) {
    _rows.append( row );
}

QString LogUlaManager::logFormated() const {

    QString log = "";

    log = std::accumulate( _rows.begin(), _rows.end(), log, []( QString log, const QString& row ){

        log.append( row + "\n" );

        return log;

    });

    return log;
}
