#ifndef REGISTERMANAGER_H
#define REGISTERMANAGER_H

#include <QList>
#include <QString>
#include <model/register/registermodel.h>

class RegisterManager{
public:
    RegisterManager();
    ~RegisterManager();

    static RegisterManager& instance();

    RegisterModel* getOne();

    bool hasRegisterByName( const QString& name ) const;

    void reset();

private:
    void init();

    QList<QString> _registersAlloc;
    QList<RegisterModel*> _registers;
};

#endif // REGISTERMANAGER_H
