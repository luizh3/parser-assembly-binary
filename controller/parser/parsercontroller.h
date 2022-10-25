#ifndef PARSERCONTROLLER_H
#define PARSERCONTROLLER_H

#include <QObject>

class ParserController : public QObject {
    Q_OBJECT
public slots:
    void makeParser( QString text ) const;
};

#endif // PARSERCONTROLLER_H
