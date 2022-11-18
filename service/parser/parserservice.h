#ifndef PARSERSERVICE_H
#define PARSERSERVICE_H

#include <QDebug>

#include <model/ula/ulamodel.h>
#include <model/binary/binaryrowmodel.h>
#include <model/result/parserresultmodel.h>
#include <model/assembly/assemblyrowmodel.h>

class ParserService {
public:
    void formatText( QString& text ) const;
    ParserResultModel* makeParser( QString dsText ) const;
private:
    ParserResultModel* toParserResult( const QList<AssemblyRowModel*>& assemblyRows, const QList<BinaryRowModel*>& binaryRows, const QList<UlaModel*>& operationsUla ) const;

    QString assemblyRowToRawText( const QList<AssemblyRowModel*>& rows ) const;
    QString binaryRowToRawText(  const QList<BinaryRowModel*>& rows ) const;
    QString operationsUlaToRawText(  const QList<UlaModel*>& operationsUla ) const;

    void toObjectsFromText( QString& dsText, QList<AssemblyRowModel*>& rowsAssembly, QList<BinaryRowModel*>& rowsBinary, QList<UlaModel*>& operationsUla ) const;

    void activeLabel( const bool result, const TipoOperacaoAssemblyEnum& tpLastOperation ) const;

    void reset() const;

    void fromAssemblyToInstruction( const AssemblyRowModel* assemblyRow, QList<BinaryRowModel*>& rowsBinary, QList<UlaModel*>& operationsUla ) const;
    void fromAssemblyToInstructions( const QList<AssemblyRowModel*>& assemblyRows, QList<BinaryRowModel*>& rowsBinary, QList<UlaModel*>& operationsUla ) const;

};

#endif // PARSERSERVICE_H
