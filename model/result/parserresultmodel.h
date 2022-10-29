#ifndef PARSERRESULTMODEL_H
#define PARSERRESULTMODEL_H

#include <QString>

class ParserResultModel {
public:
    ParserResultModel();

    const QString& dsCodeResultUla() const;
    void setDsCodeResultUla( const QString &newDsCodeResultUla );

    const QString& dsCodeResultBinary() const;
    void setDsCodeResultBinary( const QString &newDsCodeResultBinary );

    const QString& dsCodeResultAssembly() const;
    void setDsCodeResultAssembly( const QString &newDsCodeResultAssembly );

private:
    QString _dsCodeResultUla;
    QString _dsCodeResultBinary;
    QString _dsCodeResultAssembly;
};

#endif // PARSERRESULTMODEL_H
