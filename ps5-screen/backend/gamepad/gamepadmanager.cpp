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

        setCurrentDevice(GamepadType::XBOX);
    }
    else
    {
        qWarning() << "[GamepadManager]: Device" << name << "isn't supported";
        return;
    }

    threadPosixDataHandler = new QThread;
    threadPosixDataHandler->setObjectName("GPadPsxThr");

    threadEventDispatcher = new QThread;
    threadEventDispatcher->setObjectName("GPadDsptThr");

    posixDataHandler = new GamepadPosixDataHandler;
    posixDataHandler->moveToThread(threadPosixDataHandler);

    eventDispatcher = new GamepadEventDispatcher;
    eventDispatcher->moveToThread(threadEventDispatcher);

    // POSIX handler connections
    QObject::connect(threadPosixDataHandler, &QThread::finished, posixDataHandler, &GamepadPosixDataHandler::deleteLater);
    QObject::connect(this, &GamepadManager::_handleInput, posixDataHandler, &GamepadPosixDataHandler::handleInput, Qt::QueuedConnection);
    QObject::connect(posixDataHandler, &GamepadPosixDataHandler::axisChanged, this, &GamepadManager::axisChanged, Qt::QueuedConnection);

    // Event dispatcher
    QObject::connect(threadEventDispatcher, &QThread::started, eventDispatcher, &GamepadEventDispatcher::init);
    QObject::connect(threadEventDispatcher, &QThread::finished, eventDispatcher, &GamepadEventDispatcher::deleteLater);
    QObject::connect(posixDataHandler, &GamepadPosixDataHandler::actionPressed, eventDispatcher, &GamepadEventDispatcher::processActionPressed, Qt::QueuedConnection);
    QObject::connect(posixDataHandler, &GamepadPosixDataHandler::actionReleased, eventDispatcher, &GamepadEventDispatcher::processActionReleased, Qt::QueuedConnection);

    QObject::connect(eventDispatcher, &GamepadEventDispatcher::actionPressed, this, &GamepadManager::actionPressed, Qt::QueuedConnection);
    QObject::connect(eventDispatcher, &GamepadEventDispatcher::actionReleased, this, &GamepadManager::actionReleased, Qt::QueuedConnection);

    threadPosixDataHandler->start();
    threadEventDispatcher->start();

    emit _handleInput(fd);
}

GamepadManager::~GamepadManager(){}

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
