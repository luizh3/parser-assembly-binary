#ifndef VARIABLESERVICE_H
#define VARIABLESERVICE_H

#include <QString>

#include <model/variable/conditionmodel.h>

class VariableService {
public:
    QMap<QString,VariableModel*> fromTextToVariables( QString& text, const bool isLabel = false ) const;
private:
    ConditionModel* onIf( QString& text ) const;
    QMap<QString,VariableModel*> rowValuesToVariable( QList<QString>& valuesRow, const bool isLabel ) const;
    bool hasVariable( const QString& dsVariable ) const;
};

#endif // VARIABLESERVICE_H
