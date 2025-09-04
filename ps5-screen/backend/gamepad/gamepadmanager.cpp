#include "gamepadmanager.h"

GamepadManager::GamepadManager(QObject *parent)
    : QObject{parent}
{
    int fd = open(DEVICE_PATH, O_RDONLY);

    if (fd == -1)
    {
        qWarning() << "[GamepadManager]: Can't open" << DEVICE_PATH << "device";
        return;
    }

    char rawName[100];
    ioctl(fd, JSIOCGNAME(100), &rawName);

    const QString name = rawName;

    if (name == "")
    {
        qWarning() << "[GamepadManager]: Can't find any device";
        return;
    }

    qInfo() << "[GamepadManager]: Found" << name;

    if (name.toLower().contains("xbox"))
    {
        qDebug() << "[GamepadManager]: Set Xbox mapping";

        GamepadMappings::currentDeviceButtonMap = GamepadMappings::_XboxButtonMap;
        GamepadMappings::currentDeviceAxisMap = GamepadMappings::_XboxAxisMap;
        GamepadMappings::currentButtonActionMap = GamepadMappings::_XboxButtonActionMap;
    }
    else
    {
        qWarning() << "[GamepadManager]: Device" << name << "isn't supported";
        return;
    }

    thread = new QThread;
    thread->setObjectName("GPadInptThr");

    worker = new GamepadHandlerWorker();
    worker->moveToThread(thread);

    QObject::connect(this, &GamepadManager::handleInput, worker, &GamepadHandlerWorker::handleInput, Qt::QueuedConnection);
    QObject::connect(worker, &GamepadHandlerWorker::actionPressed, this, &GamepadManager::actionPressed, Qt::QueuedConnection);
    QObject::connect(worker, &GamepadHandlerWorker::actionReleased, this, &GamepadManager::actionReleased, Qt::QueuedConnection);
    QObject::connect(worker, &GamepadHandlerWorker::axisChanged, this, &GamepadManager::axisChanged, Qt::QueuedConnection);

    thread->start();

    emit handleInput(fd);
}

GamepadManager::~GamepadManager()
{
    delete worker;
}
