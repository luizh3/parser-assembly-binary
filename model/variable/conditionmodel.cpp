#include "conditionmodel.h"

ConditionModel::ConditionModel() { }

VariableModel::TypeVariableEnum ConditionModel::tpVariable() {
    return TypeVariableEnum::CONDITION;
}

const QString& ConditionModel::rawElseContent() const {
    return _rawElseContent;
}

void ConditionModel::setRawElseContent(const QString &newRawElseContent) {
    _rawElseContent = newRawElseContent;
}

const QString &ConditionModel::rawIfContent() const {
    return _rawIfContent;
}

void ConditionModel::setRawIfContent(const QString &newRawIfContent) {
    _rawIfContent = newRawIfContent;
}

const QMap<QString, VariableModel *> &ConditionModel::variablesIfContent() const
{
    return _variablesIfContent;
}

void ConditionModel::setVariablesIfContent(const QMap<QString, VariableModel *> &newVariablesIfContent)
{
    _variablesIfContent = newVariablesIfContent;
}

const QMap<QString, VariableModel *> &ConditionModel::variablesElseContent() const
{
    return _variablesElseContent;
}

void ConditionModel::setVariablesElseContent(const QMap<QString, VariableModel *> &newVariablesElseContent)
{
    _variablesElseContent = newVariablesElseContent;
}
