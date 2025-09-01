#ifndef GAMEPADMANAGER_H
#define GAMEPADMANAGER_H

#include <QDebug>
#include <QObject>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>

class GamepadManager : public QObject
{
    Q_OBJECT

public:
    explicit GamepadManager(QObject *parent = nullptr);

private:
    void run();
    int readEvent(int fd, struct js_event *event);

signals:
};

#endif // GAMEPADMANAGER_H
