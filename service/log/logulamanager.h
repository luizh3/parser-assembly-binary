#ifndef LOGULAMANAGER_H
#define LOGULAMANAGER_H

#include <QList>

class LogUlaManager {
public:
    LogUlaManager();
    static LogUlaManager& instance();

    void addRow( const QString& row );
    QString logFormated() const;

    void reset();

private:
    QList<QString> _rows;
};

#endif // LOGULAMANAGER_H
