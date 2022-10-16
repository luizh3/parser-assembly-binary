#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "controller/inputcodecontroller.h"
#include "controller/config/settingscontroller.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QCoreApplication::setOrganizationName("NotoCorporation");
    QCoreApplication::setOrganizationDomain("NoExists.com");
    QCoreApplication::setApplicationName("Parser");

    qmlRegisterType<InputCodeController>( "br.com.InputCodeController", 1, 0, "InputCodeController" );
    qmlRegisterType<SettingsController>( "br.com.SettingsController", 1, 0, "SettingsController" );

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
