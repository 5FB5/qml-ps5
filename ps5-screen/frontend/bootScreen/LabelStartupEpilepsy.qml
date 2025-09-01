import QtQuick
import QtQuick.Controls
import QtQuick.Timeline


Text {
    id: root

    property alias animRunning: timelineAnimation.running
    property alias timeline: timeline
    property alias animation: timelineAnimation

    signal animFinished()

    text: qsTr("PHOTOSENSITIVE EPILEPSY: IF YOU HAVE A HISTORY OF EPILEPSY OR SEIZURES, CONSULT A DOCTOR BEFORE USE. CERTAIN PATTERNS MAY TRIGGER SEIZURES WITH NO PRIOR HISTORY. BEFORE USING THIS PRODUCT, CAREFULLY READ THE INSTRUCTION MANUAL.")

    Timeline {
        id: timeline
        animations: [
            TimelineAnimation {
                id: timelineAnimation
                running: true
                loops: 1
                duration: 3500
                to: 1120
                from: 0

                onFinished: function()
                {
                    root.animFinished();
                }
            }
        ]
        startFrame: 0
        endFrame: 1120
        enabled: true

        KeyframeGroup {
            target: labelStartupEpilepsy
            property: "opacity"
            Keyframe {
                value: 0
                easing.bezierCurve: [0.517, -0.00575, 0.102, 1.01, 1, 1]
                frame: 50
            }

            Keyframe {
                value: 1
                easing.bezierCurve: [0.517, -0.00575, 0, 1, 1, 1]
                frame: 151
            }

            Keyframe {
                value: 1
                frame: 992
                easing.bezierCurve: [0.517, -0.00575, 0.102, 1.01, 1, 1]
            }

            Keyframe {
                value: 0
                frame: 1111
                easing.bezierCurve: [0.517, -0.00575, 0.102, 1.01, 1, 1]
            }
        }

        KeyframeGroup {
            target: labelStartupEpilepsy
            property: "scale"
            Keyframe {
                value: 0.9
                easing.bezierCurve: [0.517, -0.00575, 0.102, 1.01, 1, 1]
                frame: 50
            }

            Keyframe {
                value: 1
                easing.bezierCurve: [0.517, -0.00575, 0, 1, 1, 1]
                frame: 151
            }
        }
    }

}
