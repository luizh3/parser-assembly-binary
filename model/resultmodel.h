#ifndef RESULTMODEL_H
#define RESULTMODEL_H

#include <QString>

class ResultModel {
public:
    ResultModel();
    const QString &title() const;
    void setTitle( const QString &newTitle );

    const QString &message() const;
    void setMessage( const QString &newMessage );

    bool isError() const;
    void setIsError(bool newIsError);

private:
    bool _isError;
    QString _title;
    QString _message;
};

#endif // RESULTMODEL_H
