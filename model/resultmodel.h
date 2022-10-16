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
    QString _title;
    QString _message;
    bool _isError;
};

#endif // RESULTMODEL_H
