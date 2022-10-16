#include "settingscontroller.h"

#include <QDebug>
#include <QSettings>

#include <service/helper/utilshelper.h>

SettingsController::SettingsController() :
    _fgRunCode( false ){
    readConfigs();
}

void SettingsController::readConfigs() {

    qInfo() << "SettingsController::readConfigs";

    const bool fgRunCode = UtilsHelper::readValue( UtilsHelper::FG_RUN_CODE ).toBool();

    qInfo() << "SettingsController::readConfigs [FG_RUN_CODE]" << fgRunCode;

    setFgRunCode( fgRunCode );

}

void SettingsController::writeConfigs( const bool isRunCode ) const {

    qInfo() << "SettingsController::writeConfigs [IS_RUN_CODE]" << isRunCode;

    QSettings settings( UtilsHelper::pathConfigFile(), QSettings::IniFormat);

    settings.beginGroup( UtilsHelper::DS_CONFIGS );
    settings.setValue( UtilsHelper::FG_RUN_CODE, isRunCode );
    settings.endGroup();

    qInfo() << "SettingsController::writeConfigs";

}

bool SettingsController::isRunCode() const{
    return _fgRunCode;
}

void SettingsController::setFgRunCode( bool newFgRunCode ) {
    _fgRunCode = newFgRunCode;
    emit isRunCodeChanged();
}

