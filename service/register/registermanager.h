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

    const QList<RegisterModel*>& registers() const;
    void setRegisters( const QList<RegisterModel*>& newRegisters );

private:
    QList<QString> _registersAlloc;
    QList<RegisterModel*> _registers;
};

#endif // REGISTERMANAGER_H
