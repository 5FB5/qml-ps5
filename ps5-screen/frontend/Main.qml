import QtQuick
import QtQuick.Controls
import QtQuick.Timeline
import "bootScreen"
import "mainScreen"

Window
{
    id: root

    minimumWidth: 1600
    minimumHeight: 900
    visible: true

    title: qsTr("PS5 Screen")

    Rectangle
    {
        id: bg

        anchors.fill: parent

        states: [
            State {
                name: "Init"

                PropertyChanges {
                    target: gameInfoPanel
                    currentIndex: 0
                }

                PropertyChanges {
                    target: gamesListView
                    opacity: 0
                    visible: true
                    spacing: -100
                }

                PropertyChanges {
                    target: gamesListView.timeline
                    enabled: true
                }

                PropertyChanges {
                    target: gamesListView.startupAnimation
                    running: true
                }
            },
            State {
                name: "MainState"

                // PropertyChanges {
                //     target: gameInfoPanel
                //     currentIndex: 1
                // }

                PropertyChanges {
                    target: gamesListView
                    opacity: 1
                    spacing_: 30
                    interactive: true
                }

                PropertyChanges {
                    target: labelStartupEpilepsy.timeline
                    enabled: false
                }

                PropertyChanges {
                    target: labelStartupEpilepsy.animation
                    running: false
                }
            }
        ]

        GameInfoPanel
        {
            id: gameInfoPanel

            anchors.fill: parent
        }

        LabelStartupEpilepsy
        {
            id: labelStartupEpilepsy

            width: parent.width / 1.1
            height: parent.height / 1.5

            anchors.centerIn: parent

            animRunning: false

            font
            {
                capitalization: Font.AllUppercase
                family: "Ubuntu"
                pointSize: 20
                styleName: "Thin"
            }

            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            opacity: 0
            scale: 1
            wrapMode: Text.WordWrap

            Timer
            {
                id: timerStartup

                interval: 1000
                repeat: false
                running: true

                onTriggered: function()
                {
                    labelStartupEpilepsy.animRunning = true;
                }
            }

            onAnimFinished: function()
            {
                bg.state = "Init";
                gamesListView.state = "Init";
                gamesListView.startupAnimation.running = true;
            }
        }

        GamesListView
        {
            id: gamesListView

            anchors
            {
                top: parent.top
                left: parent.left
                right: parent.right

                margins: 100
                leftMargin: 15
                rightMargin: 0
            }

            onCurrentIndexChanged: function()
            {
                if (currentIndex === -1)
                {
                    gameInfoPanel.currentIndex = 0;
                    return;
                }

                gameInfoPanel.currentIndex = currentIndex + 1;
            }

            startupAnimation.onFinished: function()
            {
                bg.state = "MainState";
                gamesListView.state = "MainState";
            }
        }
    }
}
