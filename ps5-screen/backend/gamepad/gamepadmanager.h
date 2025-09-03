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

enum class PSButton: uint8_t
{
    CROSS = 0,
    CIRCLE,
    SQUARE,
    TRIANGLE,
    COUNT,
    UNKNOWN
};

namespace GamepadMappings
{
    inline QMap<uint8_t, QString> XboxButtonMap
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

    inline QMap<QString, QString> XboxActionMap
        {
            {   "A",        "accept"        },
            {   "B",        "cancel"        },
            {   "X",        "X event"       },
            {   "Y",        "Y event"       },
            {   "LB",       "LB event"      },
            {   "RB",       "RB event"      },
            {   "Back",     "Back event"    },
            {   "Start",    "Start event"   },
            {   "Xbox",     "Xbox event"    },
            {   "LS",       "LS event"      },
            {   "RS",       "RS event"      }
        };

    inline QMap<uint8_t, QString> currentMap;
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
