#ifndef ASSEMBLYSERVICE_H
#define ASSEMBLYSERVICE_H

#include <QList>

#include <model/assembly/assemblyrowmodel.h>

class AssemblyService {
public:
   QList<AssemblyRowModel*> fromVariablesToAssemblyRow() const;
private:
   QList<QString> toAsmInstruction( const QList<QString>& params ) const;
   AssemblyRowModel* toAssemblyRow( const QString& rawRow, const QList<QString>& values, const TipoOperacaoAssemblyEnum& tpOperation ) const;
};

#endif // ASSEMBLYSERVICE_H
