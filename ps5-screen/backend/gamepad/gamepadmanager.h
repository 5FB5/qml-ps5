#ifndef GAMEPADMANAGER_H
#define GAMEPADMANAGER_H

#include <QDebug>
#include <QThread>
#include <QObject>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>

#include "gamepadhandlerworker.h"

#define DEVICE_PATH "/dev/input/js0"

class GamepadHandlerWorker;

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
        {   10,    "RS"             },
        {   255,   "XboxGamepad"    }
    };

inline QMap<uint8_t, QString> _XboxAxisMap
    {
        {  6, "D-Pad Horizontal"    },
        {  7, "D-Pad Vertical"   }
    };

inline QMap<QString, QString> _XboxButtonActionMap
    {
        {   "A",                        "accept"                    },
        {   "B",                        "cancel"                    },
        {   "X",                        "X event"                   },
        {   "Y",                        "Y event"                   },
        {   "LB",                       "LB event"                  },
        {   "RB",                       "RB event"                  },
        {   "Back",                     "Back event"                },
        {   "Start",                    "Start event"               },
        {   "Xbox",                     "Xbox event"                },
        {   "LS",                       "LS event"                  },
        {   "RS",                       "RS event"                  },
        {   "D-Pad HorizontalRight",    "D-Pad right event"         },
        {   "D-Pad HorizontalLeft",     "D-Pad left event"          },
        {   "D-Pad VerticalUp",         "D-Pad up event"            },
        {   "D-Pad VerticalDown",       "D-Pad down event"          },
    };

inline QMap<QString, QString> currentAxisActionMap;
inline QMap<QString, QString> currentButtonActionMap;

inline QMap<uint8_t, QString> currentDeviceAxisMap;
inline QMap<uint8_t, QString> currentDeviceButtonMap;
}

class GamepadManager : public QObject
{
    Q_OBJECT

public:
    explicit GamepadManager(QObject *parent = nullptr);
    ~GamepadManager();

private:
    GamepadHandlerWorker *worker = nullptr;
    QThread *thread = nullptr;

    int fd = -1;

signals:
    void actionPressed(QString event);
    void actionReleased(QString event);

    void handleInput(int fd);
};

#endif // GAMEPADMANAGER_H
