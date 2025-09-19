import QtQuick
import QtQuick.Controls
import QtQuick.Timeline

import gamepadmanager

import "gamepadUi"
import "bootScreen"
import "mainScreen"

Window
{
    id: root

    minimumWidth: 1600
    minimumHeight: 900
    visible: true

    title: qsTr("PS5 Screen")

    color: "white"

    GPFocusScope {
        id: focusScope

        width: parent.width
        height: parent.height

        firstObject: gp2

        debugMode: true

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
                states.state = "Init";
                gamesListView.state = "Init";
                gamesListView.startupAnimation.running = true;
            }
        }

        GPFocusItem {
            id: gp1

            anchors {
                top: parent.top
                left: parent.left
                right: parent.right

                leftMargin: 100
                rightMargin: 50
            }

            neighbours {
                bottom: gp2
            }

            height: 90

            TopPanel {
                id: topPanel

                anchors.fill: parent
                opacity: 0
            }
        }

        GPFocusItem {
            id: gp2

            anchors {
                top: gp1.bottom
                left: parent.left
                right: parent.right

                margins: 100
                topMargin: 50
                // leftMargin: 15
                // rightMargin: 0
            }

            neighbours {
                top: gp1
            }

            height: 90
            // lockFocus: true

            onActionPressed: function(name) {
                if (states.state === "" || states.state === "Init")
                    return;

                switch(name) {
                case "left":
                    gamesListView.decrementCurrentIndex();
                    break;
                case "right":
                    gamesListView.incrementCurrentIndex();
                    break;
                default: break;
                }
            }

            GamesListView {
                id: gamesListView

                anchors.fill: parent
                onCurrentIndexChanged: function() {
                    if (currentIndex === -1)
                    {
                        gameInfoPanel.currentIndex = 0;
                        return;
                    }

                    gameInfoPanel.currentIndex = currentIndex + 1;
                }

                startupAnimation.onFinished: function()
                {
                    states.state = "MainState";
                    gamesListView.state = "MainState";
                }
            }
        }

        StateGroup {
            id: states

            states: [
                State {
                    name: "Init"

                    PropertyChanges {
                        target: topPanel
                        opacity: 0
                    }

                    PropertyChanges {
                        target: gameInfoPanel
                        currentIndex: 0
                    }

                    PropertyChanges {
                        target: gamesListView
                        opacity: 0
                        visible: true
                        spacing: -100
                        enabled: false
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

                    StateChangeScript {
                        name: "setFocusOnFirstSelectedItem"
                        script: function() {
                            focusScope.firstObject.forceActiveFocus();
                        }
                    }

                    PropertyChanges {
                        target: topPanel
                        opacity: 1
                    }

                    PropertyChanges {
                        target: gp2
                        focus: true
                    }

                    PropertyChanges {
                        target: gamesListView
                        opacity: 1
                        spacing_: 30
                        interactive: true
                        enabled: true
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
        }
    }
}
