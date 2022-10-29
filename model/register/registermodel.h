#ifndef REGISTERMODEL_H
#define REGISTERMODEL_H

#include <QString>

class RegisterModel{
public:
    RegisterModel( const QString& name );

    const QString& nameRegister() const;
    void setNameRegister( const QString &newNameRegister );

    bool isActive() const;
    void setFgActive( bool newFgActive );

private:
    bool _fgActive;
    QString _nameRegister;
};

#endif // REGISTERMODEL_H
