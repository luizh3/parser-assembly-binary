#ifndef ULASERVICE_H
#define ULASERVICE_H

#include <QList>

#include <model/tipooperacaoassemblyenum.h>

#include <model/binary/binaryrowmodel.h>

class UlaService {
public:
    QString process( const BinaryRowModel* rowsBinary ) const;
private:
    QList<QString> splitValues( QString value ) const;
    TipoOperacaoAssemblyEnum tpOperacaoByDsUpcode( const QString& dsUpcode ) const;

    QString sum( const QString& first, const QString& second ) const;
    QString sub( const QString& first, const QString& second ) const;
};

#endif // ULASERVICE_H
