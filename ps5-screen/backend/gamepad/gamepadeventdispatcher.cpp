#include "gamepadeventdispatcher.h"

GamepadEventDispatcher::GamepadEventDispatcher() {}

GamepadEventDispatcher::~GamepadEventDispatcher()
{
    delete timerStartPressAndHold;
    delete timerPressAndHoldLoop;
}

void GamepadEventDispatcher::init()
{
    timerStartPressAndHold = new QTimer(this);
    timerPressAndHoldLoop = new QTimer(this);

    timerStartPressAndHold->setInterval(TIMER_PRESSHOLD_START_INTERVAL);
    timerPressAndHoldLoop->setInterval(TIMER_PRESSHOLD_LOOP_INTERVAL);

    QObject::connect(timerStartPressAndHold, &QTimer::timeout, this, &GamepadEventDispatcher::startPressedActionLoopTimer);
    QObject::connect(timerPressAndHoldLoop, &QTimer::timeout, this, &GamepadEventDispatcher::processPressAndHoldAction);
}

void GamepadEventDispatcher::processActionPressed(QString actionName)
{
    currentActionName = actionName;

    emit actionPressed(currentActionName);
    timerStartPressAndHold->start();
}

void GamepadEventDispatcher::processActionReleased(QString actionName)
{
    timerStartPressAndHold->stop();
    timerPressAndHoldLoop->stop();

    currentActionName = actionName;
    emit actionReleased(currentActionName);
}

void GamepadEventDispatcher::startPressedActionLoopTimer()
{
    timerStartPressAndHold->stop();
    timerPressAndHoldLoop->start();
}

void GamepadEventDispatcher::processPressAndHoldAction()
{
    emit actionPressed(currentActionName);
}
