#ifndef GAMEPADHANDLERWORKER_H
#define GAMEPADHANDLERWORKER_H

#include <QDebug>
#include <QMutex>
#include <QObject>
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

    void handleInput(int fd);

private:
    void processButton(uint8_t index, int16_t value);
    void processButtonEvent(QString buttonName, int16_t value);
    int readEvent(int fd, js_event *event);

    QMutex mutex;

signals:
    void actionTrigerred(QString event, QString state);
};

#endif // GAMEPADHANDLERWORKER_H
