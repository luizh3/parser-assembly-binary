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
    QString beq( const QString& first, const QString& second ) const;
    QString bgt( const QString& first, const QString& second ) const;
    QString blt( const QString& first, const QString& second ) const;
    QString bne( const QString& first, const QString& second ) const;
    QString mul( const QString& first, const QString& second ) const;
    QString div( const QString& first, const QString& second ) const;

};

#endif // ULASERVICE_H
