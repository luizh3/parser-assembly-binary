#ifndef PARSERSERVICE_H
#define PARSERSERVICE_H

#include <QDebug>

class ParserService {
public:
    void formatText( QString& text ) const;
    void makeParser( QString dsText ) const;
};

#endif // PARSERSERVICE_H
