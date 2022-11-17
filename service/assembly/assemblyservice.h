#ifndef ASSEMBLYSERVICE_H
#define ASSEMBLYSERVICE_H

#include <model/assembly/assemblyrowmodel.h>

class AssemblyService {
public:
   AssemblyRowModel* toAssemblyRowByType( const TipoOperacaoAssemblyEnum& tpOperation, const QList<QString>& values ) const;
   QList<AssemblyRowModel*> fromVariablesToAssemblyRow( const QList<QString>& keyVariablesName, const bool inputLabelsVariables = false ) const;
private:
   QList<QString> toAsmInstruction( const QList<QString>& params ) const;
   QList<AssemblyRowModel*> numbersToAsmInstruction( QList<QString>& params ) const;

   AssemblyRowModel* toAssemblyRow( const QString& rawRow, const QList<QString>& values, const TipoOperacaoAssemblyEnum& tpOperation ) const;

   AssemblyRowModel* load( VariableModel* variable ) const;
   AssemblyRowModel* sub( VariableModel* variable ) const;
   QList<AssemblyRowModel*> add( VariableModel* variable ) const;
   QList<AssemblyRowModel*> mov( VariableModel* variable ) const;
   QList<AssemblyRowModel*> mul( VariableModel* variable ) const;
   QList<AssemblyRowModel*> div( VariableModel* variable ) const;

   QList<AssemblyRowModel*> bge( const VariableModel* variable ) const;
   QList<AssemblyRowModel*> beq( const VariableModel* variable ) const;
   QList<AssemblyRowModel*> bgt( const VariableModel* variable ) const;
   QList<AssemblyRowModel*> blt( const VariableModel* variable ) const;
   QList<AssemblyRowModel*> bne( const VariableModel* variable ) const;
   QList<AssemblyRowModel*> ble( const VariableModel* variable ) const;

   QList<AssemblyRowModel*> toAritmeticAssemblyRow( const QString& dsRow, VariableModel* variable ) const;
   QList<AssemblyRowModel*> toConditionAssemblyRow( const QString& dsRow, const VariableModel* variable ) const;

};

#endif // ASSEMBLYSERVICE_H
