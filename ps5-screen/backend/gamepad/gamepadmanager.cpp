#include "gamepadmanager.h"

GamepadManager::GamepadManager(QObject *parent)
    : QObject{parent}
{
    timerPressAndHold.setInterval(TIMER_PRESSHOLD_INTERVAL);

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

        setCurrentDevice(GamepadType::XBOX);
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

    QObject::connect(this, &GamepadManager::_handleInput, worker, &GamepadHandlerWorker::handleInput, Qt::QueuedConnection);
    QObject::connect(&timerPressAndHold, &QTimer::timeout, this, &GamepadManager::processPressAndHold);
    QObject::connect(worker, &GamepadHandlerWorker::actionPressed, this, &GamepadManager::processActionPressed, Qt::QueuedConnection);
    QObject::connect(worker, &GamepadHandlerWorker::actionReleased, this, &GamepadManager::processActionReleased, Qt::QueuedConnection);
    QObject::connect(worker, &GamepadHandlerWorker::axisChanged, this, &GamepadManager::axisChanged, Qt::QueuedConnection);

    thread->start();

    emit _handleInput(fd);
}

GamepadManager::~GamepadManager()
{
    delete worker;
}

GamepadManager::GamepadType GamepadManager::currentDevice() const
{
    return m_currentDevice;
}

void GamepadManager::setCurrentDevice(const GamepadType &newCurrentDevice)
{
    if (m_currentDevice == newCurrentDevice)
        return;
    m_currentDevice = newCurrentDevice;
    emit currentDeviceChanged();
}

void GamepadManager::processActionPressed(QString actionName)
{
    currentActionName = actionName;

    emit actionPressed(actionName);
    timerPressAndHold.start();
}

void GamepadManager::processActionReleased(QString actionName)
{
    timerPressAndHold.stop();
    emit actionReleased(actionName);
}

void GamepadManager::processPressAndHold()
{
    emit actionPressed(currentActionName);
}
