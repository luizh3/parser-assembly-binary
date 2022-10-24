#ifndef VARIABLEMODEL_H
#define VARIABLEMODEL_H

#include <QString>
#include <QList>

#include <model/tipooperacaoassemblyenum.h>

class VariableModel {
public:
    VariableModel();

    QList<QString> paramsWithoutOperators() const;
    TipoOperacaoAssemblyEnum tpOperation() const;

    const QString& registerName() const;

    void setRegisterName( const QString& registerName );

    void addParam( const QString& param );

    int value() const;
    void setValue( int newValue );

    const QString &type() const;
    void setType( const QString &newType );

private:
    int _value;
    QString _type;
    QString _registerName;
    QList<QString> _params;
};

#endif // VARIABLEMODEL_H
