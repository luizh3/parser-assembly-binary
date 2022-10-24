#ifndef BINARYSERVICE_H
#define BINARYSERVICE_H

#include <QString>

#include <model/tipooperacaoassemblyenum.h>
#include <model/assembly/assemblyrowmodel.h>

class BinaryService {
public:
    QList<QString> fromAssemblyToBinary( const QList<AssemblyRowModel*>& assemblyRows ) const;
private:
    QString tpOperacaoToUpcode( const TipoOperacaoAssemblyEnum& tpOperacao ) const;
};

#endif // BINARYSERVICE_H
