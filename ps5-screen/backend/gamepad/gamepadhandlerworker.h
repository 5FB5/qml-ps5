#ifndef GAMEPADHANDLERWORKER_H
#define GAMEPADHANDLERWORKER_H

#include <QDebug>
#include <QGuiApplication>
#include <QTimer>
#include <QObject>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>

#include "gamepadmanager.h"

class GamepadManager;

class GamepadHandlerWorker : public QObject
{
    Q_OBJECT
public:
    explicit GamepadHandlerWorker(QObject *parent = nullptr);
    ~GamepadHandlerWorker();

    void init();
    void handleInput(int fd);

private:
    QString currentActionName = "";

    void processPressAndHold();

    void processButton(uint8_t index, int16_t value);
    void processAxis(uint8_t index, int16_t value);

    int readEvent(int fd, js_event *event);
    float normalize(int16_t value);

    int32_t lastAxisValue = 0;

signals:
    void axisChanged(QString event, int32_t value);
    void actionPressed(QString event);
    void actionReleased(QString event);
};

#endif // GAMEPADHANDLERWORKER_H
