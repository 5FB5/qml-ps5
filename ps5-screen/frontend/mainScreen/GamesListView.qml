import QtQuick
import QtQuick.Controls
import QtQuick.Timeline
import QtMultimedia

import "../../resources/sounds/"
// import QtGraphicalEffects


ListView
{
    id: root

    property alias startupAnimation: animListView
    property alias timeline: timeline1

    property int spacing_: 30

    anchors.fill: parent

    spacing: spacing_
    opacity: 0
    orientation: ListView.Horizontal
    interactive: false
    clip: false
    reuseItems: true

    currentIndex: -1

    model: ListModel {
        ListElement {
            text_: "PlayStation Store"
        }

        ListElement {
            text_: "Title1"
        }

        ListElement {
            text_: "Title2"
        }

        ListElement {
            text_: "Title3"
        }

        ListElement {
            text_: "Title4"
        }

        ListElement {
            text_: "Title5"
        }

        ListElement {
            text_: "Title6"
        }

        ListElement {
            text_: "Title7"
        }

        ListElement {
            text_: "Title8"
        }

        ListElement {
            text_: "Title8"
        }

        ListElement {
            text_: "Title9"
        }

        ListElement {
            text_: "Title10"
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

    delegate: Rectangle
    {   
        width: index === root.currentIndex ? 250 : 150
        height: index === root.currentIndex ? 250 : 150

        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0)

        radius: index === root.currentIndex  ? 60 : 40

        Behavior on radius
        {
            NumberAnimation
            {
                easing.type: Easing.InOutQuad
                duration: 150
            }
        }

        Behavior on width
        {
            NumberAnimation
            {
                easing.type: Easing.InOutQuad
                duration: 150
            }
        }

        Behavior on height
        {
            NumberAnimation
            {
                easing.type: Easing.InOutQuad
                duration: 150
            }
        }

        Rectangle
        {
            id: delegateBorder

            anchors
            {
                fill: parent
                margins: -1
            }

            color: "transparent"
            border.color: "red"
            border.width: 4
            radius: parent.radius + border.width
            opacity: index === root.currentIndex

            Behavior on opacity
            {
                NumberAnimation
                {
                    easing.type: Easing.InOutQuad
                    duration: 150
                }
            }
        }

        Text
        {
            id: labelGame

            anchors
            {
                bottom: delegateBorder.bottom
                left: parent.right

                leftMargin: 12
            }

            width: parent.width
            opacity: (root.state === "MainState" && index === root.currentIndex) ? 1 : 0

            font
            {
                family: "Ubuntu"
                pointSize: index === root.currentIndex ? 18 : 16
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
                value: spacing_
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
                opacity: 1
                spacing: root.spacing_
                interactive: false
                currentIndex: 0
                focus: true
                snapMode: ListView.SnapToItem
                highlightRangeMode: ListView.StrictlyEnforceRange
                highlightFollowsCurrentItem: true
                highlightMoveDuration: 100
                highlightMoveVelocity: -1
                boundsBehavior: Flickable.StopAtBounds
                boundsMovement: Flickable.StopAtBounds
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
