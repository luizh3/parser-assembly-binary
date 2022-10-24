#ifndef VARIABLEMANAGER_H
#define VARIABLEMANAGER_H

#include <model/variable/variablemodel.h>

class VariableManager {
public:
    VariableManager();
    ~VariableManager();
    static VariableManager& instance();

    QList<VariableModel*> getAll() const;
    VariableModel* get( const QString& name ) const;
    void add( const QString& name, VariableModel* variable );

    QList<QString> getAllKeys() const;
private:
      QMap<QString,VariableModel*> _variables;
};
#endif // VARIABLEMANAGER_H
