#ifndef CONDITIONMODEL_H
#define CONDITIONMODEL_H

#include "QMap"
#include "variablemodel.h"

class ConditionModel : public VariableModel {
public:
    ConditionModel();

    TypeVariableEnum tpVariable() override;

    const QString &rawElseContent() const;
    void setRawElseContent(const QString &newRawElseContent);

    const QString &rawIfContent() const;
    void setRawIfContent(const QString &newRawIfContent);

    const QMap<QString, VariableModel *> &variablesIfContent() const;
    void setVariablesIfContent(const QMap<QString, VariableModel *> &newVariablesIfContent);

    const QMap<QString, VariableModel *> &variablesElseContent() const;
    void setVariablesElseContent(const QMap<QString, VariableModel *> &newVariablesElseContent);

private:
    QString _rawElseContent;
    QString _rawIfContent;

    QMap<QString,VariableModel*> _variablesIfContent;
    QMap<QString,VariableModel*> _variablesElseContent;
};

#endif // CONDITIONMODEL_H
