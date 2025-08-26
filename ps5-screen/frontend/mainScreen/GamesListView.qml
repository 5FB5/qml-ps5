import QtQuick
import QtQuick.Controls
import QtQuick.Timeline


ListView
{
    id: root

    property alias startupAnimation: animListView
    property alias timeline: timeline1

    anchors.fill: parent

    spacing: 100
    opacity: 0
    orientation: ListView.Horizontal
    interactive: false

    currentIndex: -1

    model: ListModel {
        ListElement {
            name: "Red"
            text_: "Penis"
        }

        ListElement {
            name: "Green"
            text_: "Vagina"
        }

        ListElement {
            name: "Blue"
            text_: "Anal"
        }

        ListElement {
            name: "White"
            text_: "Zalupa"
        }
    }

    Keys.onLeftPressed: function()
    {
        decrementCurrentIndex();
    }

    Keys.onRightPressed: function()
    {
        incrementCurrentIndex();
    }

    delegate: Rectangle {
        width: index === root.currentIndex ? 200 : 150
        height: index === root.currentIndex ? 200 : 150

        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0)

        radius: 40

        Behavior on width
        {
            NumberAnimation
            {
                easing.type: Easing.InOutCubic
                duration: 100
            }
        }

        Behavior on height
        {
            NumberAnimation
            {
                easing.type: Easing.InOutCubic
                duration: 100
            }
        }

        Text
        {
            id: labelGame

            anchors
            {
                top: parent.bottom
                topMargin: 5
            }

            width: parent.width
            horizontalAlignment: Qt.AlignHCenter

            opacity: root.state === "MainState" ? 1 : 0

            font
            {
                bold: true
                pointSize: 16
            }

            text: text_

            Behavior on opacity
            {
                NumberAnimation
                {
                    easing.type: Easing.InOutCubic
                    duration: 250
                }
            }
        }

        MouseArea
        {
            id: mouseArea

            anchors.fill: parent
            hoverEnabled: true
            enabled: root.interactive

            onEntered: function()
            {
                root.currentIndex = index;
            }
        }
    }

    Timeline {
        id: timeline1
        animations: [
            TimelineAnimation {
                id: animListView
                running: false
                loops: 1
                duration: 1000
                to: 1600
                from: 0
            }
        ]
        startFrame: 0
        endFrame: 1600
        enabled: false

        KeyframeGroup {
            target: root
            property: "opacity"

            Keyframe {
                value: 1
                easing.bezierCurve: [0.645, 0.045, 0.0164, 1.22, 1, 1]
                frame: 756
            }
        }

        KeyframeGroup {
            target: root
            property: "spacing"

            Keyframe {
                value: 100
                easing.bezierCurve: [0.445, 0.05, -0.105, 1.28, 1, 1]
                frame: 1173
            }

            Keyframe {
                value: -150
                frame: 0
            }

            Keyframe {
                value: -150
                frame: 526
            }
        }
    }
    states: [
        State {
            name: "Init"

            PropertyChanges {
                target: root
                opacity: 0
                visible: true
                spacing: -150
                interactive: false
            }

            PropertyChanges {
                target: timeline1
                enabled: true
            }

            PropertyChanges {
                target: animListView
                running: true
            }
        },
        State {
            name: "MainState"

            PropertyChanges {
                target: root
                focus: true
            }

            PropertyChanges {
                target: root
                opacity: 1
                spacing: 100
                interactive: true
            }

            PropertyChanges {
                target: root.timeline
                enabled: false
            }

            PropertyChanges {
                target: animListView
                running: false
            }
        }
    ]
}
