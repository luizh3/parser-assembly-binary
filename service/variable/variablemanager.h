#ifndef VARIABLEMANAGER_H
#define VARIABLEMANAGER_H

#include <QMap>
#include <model/variable/variablemodel.h>

class VariableManager {
public:
    VariableManager();
    ~VariableManager();
    static VariableManager& instance();

    QList<VariableModel*> getAll() const;
    VariableModel* get( const QString& name ) const;
    VariableModel* getByRegisterName( const QString& name ) const;

    void add( const QString& name, VariableModel* variable );

    QList<QString> getAllKeys() const;

    QList<QString> registersVariables() const;

    void reset();

private:
      QMap<QString,VariableModel*> _variables;
      //TODO This exist because map is ordered by length or size of key, now i dont have time to fix this of another way
      QList<QString> _nameVariablesOrder;

      void addNameVariable( const QString& name );
      QMap<QString,VariableModel*> variableByRegister() const;

};
#endif // VARIABLEMANAGER_H
