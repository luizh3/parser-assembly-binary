#ifndef ASSEMBLYSERVICE_H
#define ASSEMBLYSERVICE_H

#include <model/assembly/assemblyrowmodel.h>

class AssemblyService {
public:
   AssemblyRowModel* toAssemblyRowByType( const TipoOperacaoAssemblyEnum& tpOperation, const QList<QString>& values ) const;
   QList<AssemblyRowModel*> fromVariablesToAssemblyRow( const QList<QString>& keyVariablesName, const bool inputLabelsVariables = false ) const;
private:
   QList<QString> toAsmInstruction( const QList<QString>& params ) const;
   AssemblyRowModel* toAssemblyRow( const QString& rawRow, const QList<QString>& values, const TipoOperacaoAssemblyEnum& tpOperation ) const;

   AssemblyRowModel* load( VariableModel* variable ) const;
   AssemblyRowModel* sub( VariableModel* variable ) const;
   AssemblyRowModel* add( VariableModel* variable ) const;
   QList<AssemblyRowModel*> mov( VariableModel* variable ) const;

   AssemblyRowModel* bge( const VariableModel* variable ) const;
   AssemblyRowModel* beq( const VariableModel* variable ) const;
   AssemblyRowModel* bgt( const VariableModel* variable ) const;
   AssemblyRowModel* blt( const VariableModel* variable ) const;
   AssemblyRowModel* bne( const VariableModel* variable ) const;
   AssemblyRowModel* ble( const VariableModel* variable ) const;

   AssemblyRowModel* toConditionAssemblyRow( const QString& dsRow, const VariableModel* variable ) const;

};

#endif // ASSEMBLYSERVICE_H
