#ifndef GAMEPADPOSIXDATAHANDLER_H
#define GAMEPADPOSIXDATAHANDLER_H

#include <QDebug>
#include <QGuiApplication>
#include <QTimer>
#include <QMutexLocker>
#include <QMutex>
#include <QObject>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>

#include "gamepadmanager.h"

class GamepadManager;

class GamepadPosixDataHandler: public QObject
{
    Q_OBJECT

public:
    explicit GamepadPosixDataHandler(QObject *parent = nullptr);
    ~GamepadPosixDataHandler();

    void handleInput(int fd);

private:
    void processButton(uint8_t index, int16_t value);
    void processAxis(uint8_t index, int16_t value);

    int readEvent(int fd, js_event *event);
    float normalize(int16_t value);

    float lastAxisValue = 0;

    bool actionByAxisAlreadyPressed = false;

    bool horizontalAxisPressed = false;
    bool verticalAxisPressed = false;

    float lastHorizontalAxisValue = 0.0f;
    float lastVerticalAxisValue = 0.0f;

    QMutex mutex;

signals:
    void axisChanged(QString event, int32_t value);
    void actionPressed(QString event);
    void actionReleased(QString event);
};

#endif // GamepadPosixDataHandler_H
