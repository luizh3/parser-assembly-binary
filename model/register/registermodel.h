#ifndef REGISTERMODEL_H
#define REGISTERMODEL_H

#include <QString>

class RegisterModel{
public:
    RegisterModel( const QString& name, const QString& memory = "" );

    const QString& nameRegister() const;
    void setNameRegister( const QString &newNameRegister );

    bool isActive() const;
    void setFgActive( bool newFgActive );

    const QString &binaryMemory() const;
    void setBinaryMemory(const QString &newBinaryMemory);

private:
    bool _fgActive;
    QString _nameRegister;
    QString _binaryMemory;
};

#endif // REGISTERMODEL_H
