#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

#include <QObject>

class SettingsController : public QObject {
    Q_OBJECT
    Q_PROPERTY( bool isRunCode READ isRunCode NOTIFY isRunCodeChanged );
public:
    SettingsController();

    bool isRunCode() const;
    void setFgRunCode( bool newFgRunCode );

public slots:
    void writeConfigs( const bool isRunCode ) const;

signals:
    void isRunCodeChanged();

private:
    bool _fgRunCode;

    void readConfigs();

};

#endif // SETTINGSCONTROLLER_H
