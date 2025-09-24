#ifndef GAMEPADMANAGER_H
#define GAMEPADMANAGER_H

#include <QDebug>
#include <QThread>
#include <QObject>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>

#include "gamepadposixdatahandler.h"
#include "gamepadeventdispatcher.h"

#define DEVICE_PATH "/dev/input/js0"

#define JOYSTICK_MAX_VALUE 32767
#define JOYSTICK_MIN_VALUE -32767

#define DEAD_ZONE 0.1

#define STICK_ACTION_THRESHOLD 0.6f

class GamepadPosixDataHandler;

namespace GamepadMappings
{
inline QMap<uint8_t, QString> _XboxButtonMap
    {
        {   0,     "A"              },
        {   1,     "B"              },
        {   2,     "X"              },
        {   3,     "Y"              },
        {   4,     "LB"             },
        {   5,     "RB"             },
        {   6,     "Back"           },
        {   7,     "Start"          },
        {   8,     "Xbox"           },
        {   9,     "LS"             },
        {   10,    "RS"             }
    };

inline QMap<uint8_t, QString> _XboxAxisMap
    {
        {   0, "Left stick Horizontal"      },
        {   1, "Left stick Vertical"        },
        {   3, "Right stick Horizontal"     },
        {   4, "Right stick Vertical"       },
        {   6, "D-Pad Horizontal"           },
        {   7, "D-Pad Vertical"             }
    };

inline QMap<QString, QString> _XboxButtonActionMap
    {
        {   "A",                            "accept"            },
        {   "B",                            "cancel"            },
        {   "X",                            "X event"           },
        {   "Y",                            "Y event"           },
        {   "LB",                           "LB event"          },
        {   "RB",                           "RB event"          },
        {   "Back",                         "Back event"        },
        {   "Start",                        "Start event"       },
        {   "Xbox",                         "Xbox event"        },
        {   "LS",                           "ls button"         },
        {   "RS",                           "rs button"         },
        {   "Left stick VerticalUp",        "up"                },
        {   "Left stick VerticalDown",      "down"              },
        {   "Left stick HorizontalLeft",    "left"              },
        {   "Left stick HorizontalRight",   "right"             },
        {   "D-Pad HorizontalRight",        "right"             },
        {   "D-Pad HorizontalLeft",         "left"              },
        {   "D-Pad VerticalUp",             "up"                },
        {   "D-Pad VerticalDown",           "down"              },
    };

inline QMap<QString, QString> currentAxisActionMap;
inline QMap<QString, QString> currentButtonActionMap;

inline QMap<uint8_t, QString> currentDeviceAxisMap;
inline QMap<uint8_t, QString> currentDeviceButtonMap;
}

class GamepadManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(GamepadType currentDevice READ currentDevice WRITE setCurrentDevice NOTIFY currentDeviceChanged FINAL)

public:
    explicit GamepadManager(QObject *parent = nullptr);
    ~GamepadManager();

    enum class GamepadType: uint8_t
    {
        XBOX = 0,
        PS,
        SWITCH1_PRO
    };
    Q_ENUM(GamepadType);

    GamepadType currentDevice() const;
    void setCurrentDevice(const GamepadType &newCurrentDevice);

private:
    GamepadPosixDataHandler *posixDataHandler = nullptr;
    GamepadEventDispatcher *eventDispatcher = nullptr;

    QThread *threadPosixDataHandler = nullptr;
    QThread *threadEventDispatcher = nullptr;

    int fd = -1;

    GamepadType m_currentDevice;

signals:
    void axisChanged(QString event, int32_t value);
    void actionPressed(QString event);
    void actionReleased(QString event);

    void _handleInput(int fd);
    void currentDeviceChanged();

    void test();
};

#endif // GAMEPADMANAGER_H
