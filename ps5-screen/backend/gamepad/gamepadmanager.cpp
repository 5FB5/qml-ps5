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

    qInfo() << "[GamepadManager]: Found" << name;

    if (name.toLower().contains("xbox"))
    {
        future = QtConcurrent::run(handleXboxInput, fd);
    }
}

void GamepadManager::handleXboxInput(int fd)
{
    struct js_event event;

    while(readEvent(fd, &event) == 0)
    {
        switch(event.type)
        {
        case JS_EVENT_BUTTON:
        {
            qDebug() << XboxButton[event.number];
            break;
        }
        default: break;
        }

        fflush(stdout);
    }

    close(fd);
}

int GamepadManager::readEvent(int fd, js_event *event)
{
    ssize_t bytes;

    bytes = read(fd, event, sizeof(*event));

    if (bytes == sizeof(*event))
        return 0;

    return -1;
}

void GamepadManager::getButton(uint8_t button, int16_t value)
{
    // if (deviceInfo.name.contains("Xbox"))
    // {
    //     deviceInfo.buttonInfo.pressed = static_cast<bool>(value);
    //     switch(button)
    //     {
    //     case 0:
    //     {
    //         deviceInfo.buttonInfo.name = "A";
    //         break;
    //     }
    //     case 1:
    //     {
    //         deviceInfo.buttonInfo.name = "B";
    //         break;
    //     }
    //     case 2:
    //     {
    //         deviceInfo.buttonInfo.name = "X";
    //         break;
    //     }
    //     case 3:
    //     {
    //         deviceInfo.buttonInfo.name = "Y";
    //         break;
    //     }
    //     case 4:
    //     {
    //         deviceInfo.buttonInfo.name = "LB";
    //         break;
    //     }
    //     case 5:
    //     {
    //         deviceInfo.buttonInfo.name = "RB";
    //         break;
    //     }
    //     case 6:
    //     {
    //         deviceInfo.buttonInfo.name = "Back";
    //         break;
    //     }
    //     case 7:
    //     {
    //         deviceInfo.buttonInfo.name = "Start";
    //         break;
    //     }
    //     case 8:
    //     {
    //         deviceInfo.buttonInfo.name = "Home";
    //         break;
    //     }
    //     case 9:
    //     {
    //         deviceInfo.buttonInfo.name = "LS";
    //         break;
    //     }
    //     case 10:
    //     {
    //         deviceInfo.buttonInfo.name = "RS";
    //         break;
    //     }
    //     default:
    //     {
    //         deviceInfo.buttonInfo.name = QString::number(button);
    //         break;
    //     }
    //     }
    // }
}
