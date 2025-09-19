#include "gamepadhandlerworker.h"

GamepadHandlerWorker::GamepadHandlerWorker(QObject *parent)
    : QObject{parent} {}

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
        emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceButtonMap[index]]);
    else
        emit actionReleased(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceButtonMap[index]]);
}

void GamepadHandlerWorker::processAxis(uint8_t index, int16_t value)
{
    float normalizedValue = normalize(value);

    QString axisName = GamepadMappings::currentDeviceAxisMap[index].toLower();

    if (axisName.contains("d-pad horizontal"))
    {
        if (normalizedValue == 0)
        {
            if (lastAxisValue > 0)
                emit actionReleased(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Right"]);
            else if (lastAxisValue < 0)
                emit actionReleased(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Left"]);
            return;
        }

        if (normalizedValue > 0)
        {
            currentActionName = GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Right"];
            emit actionPressed(currentActionName);
        }
        else if (normalizedValue < 0)
        {
            currentActionName = GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Left"];
            emit actionPressed(currentActionName);
        }

        lastAxisValue = normalizedValue;
    }
    else if (axisName.contains("d-pad vertical"))
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
        {
            currentActionName = GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Down"];
            emit actionPressed(currentActionName);
        }
        else if (normalizedValue < 0)
        {
            currentActionName = GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Up"];
            emit actionPressed(currentActionName);
        }
    }
    else if (axisName.contains("stick horizontal"))
    {
        if (normalizedValue == 0)
        {
            if (lastAxisValue == 1.f)
                emit actionReleased(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Right"]);
            else if (lastAxisValue == -1.f)
                emit actionReleased(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Left"]);
            return;
        }

        if (normalizedValue == 1.f || normalizedValue == -1.f)
            lastAxisValue = normalizedValue;

        if (normalizedValue == 1.f)
        {
            currentActionName = GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Right"];
            emit actionPressed(currentActionName);
        }
        else if (normalizedValue == -1.f)
        {
            currentActionName = GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Left"];
            emit actionPressed(currentActionName);
        }
    }
    else if (axisName.contains("stick vertical"))
    {
        if (normalizedValue == 1.f)
        {
            currentActionName = GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Down"];
            emit actionPressed(currentActionName);
        }
        else if (normalizedValue == -1.f)
        {
            currentActionName = GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Up"];
            emit actionPressed(currentActionName);
        }
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
