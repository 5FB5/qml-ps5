#ifndef GAMEPADMANAGER_H
#define GAMEPADMANAGER_H

#include <QDebug>
#include <QFuture>
#include <QSharedPointer>
#include <QtConcurrent/QtConcurrent>
#include <QObject>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>

#define DEVICE_PATH "/dev/input/js0"

enum class PSButton: uint8_t
{
    CROSS = 0,
    CIRCLE,
    SQUARE,
    TRIANGLE,
    COUNT,
    UNKNOWN
};

inline QMap<uint8_t, QString> XboxButton
    {
        {   0,     "accept"     },
        {   1,     "cancel"     },
        {   2,     "X"          },
        {   3,     "Y"          },
        {   4,     "LB"         },
        {   5,     "RB"         },
        {   6,     "Back"       },
        {   7,     "Start"      },
        {   8,     "Xbox"       },
        {   9,     "LS"         },
        {   10,    "RS"         }
    };

class GamepadManager : public QObject
{
    Q_OBJECT

public:
    explicit GamepadManager(QObject *parent = nullptr);

private:
    static void handleXboxInput(int fd);
    static int readEvent(int fd, js_event *event);

    static void getButton(uint8_t button, int16_t value);

    QFuture<void> future;

    void test();

signals:
    void actionTriggered(QString name, QString state);
};

#endif // GAMEPADMANAGER_H
