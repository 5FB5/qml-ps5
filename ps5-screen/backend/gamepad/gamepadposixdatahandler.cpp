#include "gamepadposixdatahandler.h"

GamepadPosixDataHandler::GamepadPosixDataHandler(QObject *parent)
    : QObject{parent} {}

GamepadPosixDataHandler::~GamepadPosixDataHandler() {}

void GamepadPosixDataHandler::handleInput(int fd)
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

int GamepadPosixDataHandler::readEvent(int fd, js_event *event)
{
    ssize_t bytes;

    bytes = read(fd, event, sizeof(*event));

    if (bytes == sizeof(*event))
        return 0;

    close(fd);

    return -1;
}

void GamepadPosixDataHandler::processButton(uint8_t index, int16_t value)
{
    if (value)
        emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceButtonMap[index]]);
    else
        emit actionReleased(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceButtonMap[index]]);
}

void GamepadPosixDataHandler::processAxis(uint8_t index, int16_t value)
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
            emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Right"]);
        else if (normalizedValue < 0)
            emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Left"]);

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
            emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Down"]);
        else if (normalizedValue < 0)
            emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Up"]);
    }
    else if (axisName.contains("stick horizontal"))
    {
        // Stick released
        if (qAbs(normalizedValue) > 0.0f && qAbs(normalizedValue) <= STICK_ACTION_THRESHOLD)
        {
            if (lastHorizontalAxisValue >= STICK_ACTION_THRESHOLD)
            {
                horizontalAxisPressed = false;
                emit actionReleased(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Right"]);
            }
            else if (lastHorizontalAxisValue <= -STICK_ACTION_THRESHOLD)
            {
                horizontalAxisPressed = false;
                emit actionReleased(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Left"]);
            }

            return;
        }

        if (horizontalAxisPressed)
            return;

        // Stick hold
        if (normalizedValue >= STICK_ACTION_THRESHOLD)
        {
            horizontalAxisPressed = true;

            emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Right"]);
        }
        else if (normalizedValue <= -STICK_ACTION_THRESHOLD)
        {
            horizontalAxisPressed = true;

            emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Left"]);
        }

        lastHorizontalAxisValue = normalizedValue;
    }
    else if (axisName.contains("stick vertical"))
    {
        // Stick released
        if (qAbs(normalizedValue) > 0.0f && qAbs(normalizedValue) <= STICK_ACTION_THRESHOLD)
        {
            if (lastVerticalAxisValue >= STICK_ACTION_THRESHOLD)
            {
                verticalAxisPressed = false;
                emit actionReleased(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Down"]);
            }
            else if (lastVerticalAxisValue <= -STICK_ACTION_THRESHOLD)
            {
                verticalAxisPressed = false;
                emit actionReleased(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Up"]);
            }

            return;
        }

        lastVerticalAxisValue = normalizedValue;

        if (verticalAxisPressed)
            return;

        // Stick hold
        if (normalizedValue >= STICK_ACTION_THRESHOLD)
        {
            verticalAxisPressed = true;
            emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Down"]);
        }
        else if (normalizedValue <= -STICK_ACTION_THRESHOLD)
        {
            verticalAxisPressed = true;
            emit actionPressed(GamepadMappings::currentButtonActionMap[GamepadMappings::currentDeviceAxisMap[index] + "Up"]);
        }
    }
    else
    {
        emit axisChanged(GamepadMappings::currentDeviceAxisMap[index], normalizedValue);
    }
}

float GamepadPosixDataHandler::normalize(int16_t value)
{
    float result = 0.0;    

    result = 2.0 * (value - JOYSTICK_MIN_VALUE) / (JOYSTICK_MAX_VALUE - JOYSTICK_MIN_VALUE) - 1.0;

    if (std::abs(result) < DEAD_ZONE)
        return 0.0;

    return result;
}

