#ifndef VARIABLEMODEL_H
#define VARIABLEMODEL_H

#include <QString>
#include <QList>

#include <model/register/registermodel.h>
#include <model/tipooperacaoassemblyenum.h>

class VariableModel {
public:
    VariableModel();

    QList<QString> paramsWithoutOperators() const;
    TipoOperacaoAssemblyEnum tpOperation() const;

    void addParam( const QList<QString>& params );
    void addParam( const QString& param );

    int value() const;
    void setValue( int newValue );

    const QString& type() const;
    void setType( const QString& newType );

    RegisterModel* getRegister() const;
    void setRegister(RegisterModel *newRegister);

    bool isLabel() const;
    void setIsLabel(bool newIsLabel);

private:
    RegisterModel* _register;
    int _value;
    bool _isLabel;
    QString _type;
    QList<QString> _params;
};

#endif // VARIABLEMODEL_H
