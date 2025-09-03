#include "gamepadhandlerworker.h"

GamepadHandlerWorker::GamepadHandlerWorker(QObject *parent)
    : QObject{parent}
{}

void GamepadHandlerWorker::handleInput(int fd)
{
    struct js_event event;

    while(readEvent(fd, &event) == 0)
    {
        switch(event.type)
        {
        case JS_EVENT_BUTTON:
        {
            processButton(event.number, event.value);
            break;
        }
        default: break;
        }

        fflush(stdout);
    }

    close(fd);
}

void GamepadHandlerWorker::processButton(uint8_t index, int16_t value)
{
    if (GamepadMappings::currentMap[255] == "XboxGamepad")
    {
        qDebug() << "[GamepadHandlerWorker]: Call event" << GamepadMappings::XboxActionMap[GamepadMappings::currentMap[index]] << (value ? "pressed" : "released");
        emit actionTrigerred(GamepadMappings::XboxActionMap[GamepadMappings::currentMap[index]], value ? "pressed" : "released");
    }
}

int GamepadHandlerWorker::readEvent(int fd, js_event *event)
{
    ssize_t bytes;

    bytes = read(fd, event, sizeof(*event));

    if (bytes == sizeof(*event))
        return 0;

    return -1;
}
