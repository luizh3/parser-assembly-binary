#ifndef ASSEMBLYROWMODEL_H
#define ASSEMBLYROWMODEL_H

#include <QList>
#include <QString>

#include <model/tipooperacaoassemblyenum.h>

class AssemblyRowModel {
public:
    AssemblyRowModel();

    TipoOperacaoAssemblyEnum typeOperation() const;
    void setTypeOperation(TipoOperacaoAssemblyEnum newTypeOperation);

    const QList<QString>& values() const;
    void setValues(const QList<QString>& newValues);

    const QString &rawTextRow() const;
    void setRawTextRow( const QString& newRawTextRow );

    const QString &addressMemoryRow() const;
    void setAddressMemoryRow( const QString& newAddressMemoryRow );

private:
    TipoOperacaoAssemblyEnum _typeOperation;
    QString _rawTextRow;
    QString _addressMemoryRow;
    QList<QString> _values;
};

#endif // ASSEMBLYROWMODEL_H
