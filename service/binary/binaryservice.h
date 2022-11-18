#ifndef BINARYSERVICE_H
#define BINARYSERVICE_H

#include <QString>

#include <model/binary/binaryrowmodel.h>
#include <model/tipooperacaoassemblyenum.h>
#include <model/assembly/assemblyrowmodel.h>

class BinaryService {
public:
    BinaryRowModel* fromAssemblyToBinary( const AssemblyRowModel* assemblyRows ) const;
    int fromBinary( const QString& binary ) const;
    QString toBinary( unsigned int number ) const;
    QMap<TipoOperacaoAssemblyEnum,QString> mapDsUpCodeByTp() const;
private:
    QString tpOperacaoToUpcode( const TipoOperacaoAssemblyEnum& tpOperacao ) const;
};

#endif // BINARYSERVICE_H
