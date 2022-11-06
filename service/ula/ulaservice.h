#ifndef ULASERVICE_H
#define ULASERVICE_H

#include <QList>

#include <model/ula/ulamodel.h>
#include <model/binary/binaryrowmodel.h>
#include <model/tipooperacaoassemblyenum.h>

class UlaService {
public:
    UlaModel* process( const BinaryRowModel* rowsBinary ) const;
private:
    QList<QString> splitValues( QString value ) const;
    TipoOperacaoAssemblyEnum tpOperacaoByDsUpcode( const QString& dsUpcode ) const;

    QString sum( const QString& first, const QString& second ) const;
    QString sub( const QString& first, const QString& second ) const;
    QString bge( const QString& first, const QString& second ) const;
    QString ble( const QString& first, const QString& second ) const;
};

#endif // ULASERVICE_H
