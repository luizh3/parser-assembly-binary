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
