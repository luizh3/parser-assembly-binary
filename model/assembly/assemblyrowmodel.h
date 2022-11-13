#ifndef ASSEMBLYROWMODEL_H
#define ASSEMBLYROWMODEL_H

#include <QList>
#include <QString>

#include <model/variable/variablemodel.h>
#include <model/tipooperacaoassemblyenum.h>

class AssemblyRowModel {
public:
    AssemblyRowModel();

    TipoOperacaoAssemblyEnum typeOperation() const;
    void setTypeOperation(TipoOperacaoAssemblyEnum newTypeOperation);

    const QList<QString>& values() const;
    void setValues(const QList<QString>& newValues);

    const QString& rawTextRow() const;
    void setRawTextRow( const QString& newRawTextRow );

    const QString& addressMemoryRow() const;
    void setAddressMemoryRow( const QString& newAddressMemoryRow );

    VariableModel *variableResultOperation() const;
    void setVariableResultOperation( VariableModel *newVariableResultOperation );

    bool isSkip() const;
    void setIsSkip(bool newIsSkip);

private:
    VariableModel* _variableResultOperation;
    bool _isSkip;
    TipoOperacaoAssemblyEnum _typeOperation;
    QString _rawTextRow;
    QString _addressMemoryRow;
    QList<QString> _values;
};

#endif // ASSEMBLYROWMODEL_H
