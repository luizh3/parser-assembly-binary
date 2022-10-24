#ifndef REGISTERMANAGER_H
#define REGISTERMANAGER_H

#include <QList>
#include <QString>

class RegisterManager{
public:
    RegisterManager();
    static RegisterManager& instance();

    QString getOne();

private:
    QList<QString> _nameRegisters;
};

#endif // REGISTERMANAGER_H
