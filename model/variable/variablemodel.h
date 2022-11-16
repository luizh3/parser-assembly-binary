#ifndef VARIABLEMODEL_H
#define VARIABLEMODEL_H

#include <QString>
#include <QList>

#include <model/register/registermodel.h>
#include <model/tipooperacaoassemblyenum.h>

class VariableModel {
public:
    VariableModel();
    virtual ~VariableModel() = default;
    VariableModel( const VariableModel* variable );

    enum class TypeVariableEnum : int {
        VARIABLE,
        CONDITION
    };

    virtual TypeVariableEnum tpVariable();

    QList<QString> paramsWithoutOperators() const;
    TipoOperacaoAssemblyEnum tpOperation( const bool isAlreadyAllocated = false ) const;

    void addParam( const QList<QString>& params );
    void addParam( const QString& param );
    QList<QString> params() const;
    void clearParams();

    int value() const;
    void setValue( int newValue );

    const QString& type() const;
    void setType( const QString& newType );

    RegisterModel* getRegister() const;
    void setRegister( RegisterModel *newRegister );

    bool isLabel() const;
    void setIsLabel( bool newIsLabel );

    void setTpOperation( const TipoOperacaoAssemblyEnum& tpOperation );

private:
    RegisterModel* _register;
    TipoOperacaoAssemblyEnum _tpOperation;
    int _value;
    bool _isLabel;
    QString _type;
    QList<QString> _params;
};

#endif // VARIABLEMODEL_H
