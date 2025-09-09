#include "gamepadhandlerworker.h"

GamepadHandlerWorker::GamepadHandlerWorker(QObject *parent)
    : QObject{parent}
{}

GamepadHandlerWorker::~GamepadHandlerWorker() {}

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

void GamepadHandlerWorker::processButton(uint8_t index, int16_t normalizedValue)
{
    if (normalizedValue)
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
    float normalizedValue = normalize(value);

    if (GamepadMappings::currentDeviceAxisMap[index].toLower().contains("d-pad horizontal"))
    {
        if (normalizedValue == 0)
        {
            if (lastAxisValue > 0)
                emit actionReleased(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Right"]);
            else if (lastAxisValue < 0)
                emit actionReleased(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Left"]);
            return;
        }

        lastAxisValue = normalizedValue;

        if (normalizedValue > 0)
            emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Right"]);
        else if (normalizedValue < 0)
            emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Left"]);
    }
    else if (GamepadMappings::currentDeviceAxisMap[index].toLower().contains("d-pad vertical"))
    {
        if (normalizedValue == 0)
        {
            if (lastAxisValue > 0)
                emit actionReleased(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Down"]);
            else if (lastAxisValue < 0)
                emit actionReleased(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Up"]);
            return;
        }

        lastAxisValue = normalizedValue;

        if (normalizedValue > 0)
            emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Down"]);
        else if (normalizedValue < 0)
            emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Up"]);
    }
    else if (GamepadMappings::currentDeviceAxisMap[index].toLower().contains("stick horizontal"))
    {
        if (normalizedValue == 1.f)
            emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Right"]);
        else if (normalizedValue == -1.f)
            emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Left"]);

    }
    else if (GamepadMappings::currentDeviceAxisMap[index].toLower().contains("stick vertical"))
    {
        if (normalizedValue == 1.f)
            emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Down"]);
        else if (normalizedValue == -1.f)
            emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Up"]);
    }
    else
    {
        emit axisChanged(GamepadMappings::currentDeviceAxisMap[index], normalizedValue);
    }
}

float GamepadHandlerWorker::normalize(int16_t value)
{
    float result = 0.0;
    float normalized = 0.0;
    float sign = 0.0;

    result = 2.0 * (value - JOYSTICK_MIN_VALUE) / (JOYSTICK_MAX_VALUE - JOYSTICK_MIN_VALUE) - 1.0;

    if (std::abs(result) < DEAD_ZONE)
        return 0.0;

    return result;
}

int GamepadHandlerWorker::readEvent(int fd, js_event *event)
{
    ssize_t bytes;

    bytes = read(fd, event, sizeof(*event));

    if (bytes == sizeof(*event))
        return 0;

    return -1;
}
