#include "gamepadhandlerworker.h"

GamepadHandlerWorker::GamepadHandlerWorker(QObject *parent)
    : QObject{parent}
{}

void GamepadHandlerWorker::handleInput(int fd)
{
    struct js_event event;

    while(readEvent(fd, &event) == 0)
    {
        if (QGuiApplication::applicationState() == Qt::ApplicationInactive)
            continue;

        switch(event.type)
        {
        case JS_EVENT_BUTTON:
        {
            processButton(event.number, event.value);
            break;
        }
        case JS_EVENT_AXIS:
        {
            processAxis(event.number, event.value);
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
    if (value)
    {
        // qDebug() << "[GamepadHandlerWorker]: Call event" << GamepadMappings::XboxActionMap[GamepadMappings::currentMap[index]] << "pressed";
        emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceButtonMap[index]]);
    }
    else
    {
        // qDebug() << "[GamepadHandlerWorker]: Call event" << GamepadMappings::XboxActionMap[GamepadMappings::currentMap[index]] << "released";
        emit actionReleased(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceButtonMap[index]]);
    }
}

void GamepadHandlerWorker::processAxis(uint8_t index, int16_t value)
{
    if (GamepadMappings::currentDeviceAxisMap[index].contains("D-Pad Horizontal"))
    {
        if (value == 0)
        {
            if (lastAxisValue > 0)
                emit actionReleased(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Right"]);
            else if (lastAxisValue < 0)
                emit actionReleased(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Left"]);
            return;
        }

        lastAxisValue = value;

        if (value > 0)
            emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Right"]);
        else if (value < 0)
            emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Left"]);
    }
    else if (GamepadMappings::currentDeviceAxisMap[index].contains("D-Pad Vertical"))
    {
        if (value == 0)
        {
            if (lastAxisValue > 0)
                emit actionReleased(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Down"]);
            else if (lastAxisValue < 0)
                emit actionReleased(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Up"]);
            return;
        }

        lastAxisValue = value;

        if (value > 0)
            emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Down"]);
        else if (value < 0)
            emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Up"]);
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
