#ifndef GAMEPADEVENTDISPATCHER_H
#define GAMEPADEVENTDISPATCHER_H

#include <QTimer>
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
#include <QObject>

#define TIMER_PRESSHOLD_START_INTERVAL 380
#define TIMER_PRESSHOLD_LOOP_INTERVAL 30

class GamepadEventDispatcher : public QObject
{
    Q_OBJECT

public:
    GamepadEventDispatcher();
    ~GamepadEventDispatcher();

private:
    QTimer *timerStartPressAndHold = nullptr;
    QTimer *timerPressAndHoldLoop = nullptr;

    QString currentActionName = "";

    bool actionAlreadyPressed = false;

    void processPressAndHold();

public slots:
    void init();

    void processActionPressed(QString actionName);
    void processActionReleased(QString actionName);

private slots:
    void startPressedActionLoopTimer();
    void processPressAndHoldAction();

signals:
    void axisChanged(QString event, int32_t value);
    void actionPressed(QString event);
    void actionReleased(QString event);
};

#endif // GAMEPADEVENTDISPATCHER_H
