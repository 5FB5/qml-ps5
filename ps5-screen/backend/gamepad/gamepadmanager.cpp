#include "gamepadmanager.h"

GamepadManager::GamepadManager(QObject *parent)
    : QObject{parent}
{
    run();
}

void GamepadManager::run()
{
    int fd = open("/dev/input/js0", O_RDONLY);

    if (fd == -1)
    {
        qWarning() << "[GamepadManager]: Can't open dev/input/js0 device";
        return;
    }

    struct js_event event;

    while(readEvent(fd, &event) == 0)
    {
        switch(event.type)
        {
        case JS_EVENT_BUTTON:
        {
            qDebug() << "Button: " << event.number << (event.value ? "pressed" : "released");
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
