#ifndef INPUTCODECONTROLLER_H
#define INPUTCODECONTROLLER_H

#include <functional>

#include <QObject>
#include <QProcess>

class InputCodeController : public QObject {
    Q_OBJECT
public:
    enum MessageTypeEnum{
        ERROR,
        SUCCESS,
    };

    Q_ENUM( MessageTypeEnum );

public slots:
    void writeText( const QString& text ) const;
    QString readText() const;
    void onRunCode() const;

    void runSync( const std::function<void()>& function ) const;
signals:
    void showMessage( MessageTypeEnum tpMessage, const QString title, const QString value ) const;
private:
    QByteArray execCode() const;
    void buildCode() const;
    void execProcess(const QString& path, const QString& executable, std::function<void( const QByteArray& value )> readFunction ) const;
};

#endif // INPUTCODECONTROLLER_H
