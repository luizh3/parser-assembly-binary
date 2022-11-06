#ifndef ASSEMBLYSERVICE_H
#define ASSEMBLYSERVICE_H

#include <model/assembly/assemblyrowmodel.h>

class AssemblyService {
public:
   QList<AssemblyRowModel*> fromVariablesToAssemblyRow( const QList<QString>& keyVariablesName, const bool inputLabelsVariables = false ) const;
private:
   QList<QString> toAsmInstruction( const QList<QString>& params ) const;
   AssemblyRowModel* toAssemblyRow( const QString& rawRow, const QList<QString>& values, const TipoOperacaoAssemblyEnum& tpOperation ) const;

   QList<AssemblyRowModel*> bge( VariableModel* variable ) const;
};

#endif // ASSEMBLYSERVICE_H
