#ifndef ULASERVICE_H
#define ULASERVICE_H

#include <QList>

#include <model/tipooperacaoassemblyenum.h>

#include <model/binary/binaryrowmodel.h>

class UlaService {
public:
    void process( const QList<BinaryRowModel*>& rowsBinary ) const;
private:
    QList<QString> splitValues( QString value ) const;
    TipoOperacaoAssemblyEnum tpOperacaoByDsUpcode( const QString& dsUpcode ) const;

    void sum( const QString& first, const QString& second ) const;
    void sub( const QString& first, const QString& second ) const;
};

#endif // ULASERVICE_H
