#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "gamepadmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    const QUrl url = QUrl(QStringLiteral("qrc:/frontend/Main.qml"));

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    GamepadManager manager;

    return app.exec();
}
