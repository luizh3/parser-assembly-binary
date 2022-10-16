#ifndef SERVICEEXCEPTION_H
#define SERVICEEXCEPTION_H

#include <stdexcept>

#include <QString>

class ServiceException : public std::runtime_error {
public:
    ServiceException( const QString& what, const QString& value );

    const QString& value() const;
    void setValue( const QString &newValue );

private:
    QString _value;
};

#endif // SERVICEEXCEPTION_H
