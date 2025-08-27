import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

StackLayout
{
    id: root

    property int panelAnimationSpeed: 600

    onCurrentIndexChanged: function()
    {
        for (let i = 0; i < children.length; i++)
        {
            let leftPanel = children[currentIndex - 1];
            let midPanel = children[currentIndex];
            let rightPanel = children[currentIndex + 1];

            if (!(midPanel instanceof Rectangle))
                continue;

            // if (!(leftPanel instanceof Rectangle))
            //     continue;

            if (!(rightPanel instanceof Rectangle))
                continue;

            if (leftPanel)
                leftPanel.opacity = 0;

            rightPanel.opacity = 0;
            midPanel.opacity = 1;

            return;
        }
    }

    Rectangle
    {
        color: 'transparent'
        width: parent.width
        height: parent.height
        opacity: 0

        // Animates opacity change
        Behavior on opacity {
            NumberAnimation {
                easing.type: Easing.InOutCubic
                duration: root.panelAnimationSpeed
            }
        }
    }

    Rectangle
    {
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0)
        width: parent.width
        height: parent.height
        opacity: 0

        // Animates opacity change
        Behavior on opacity {
            NumberAnimation {
                easing.type: Easing.InOutCubic
                duration: root.panelAnimationSpeed
            }
        }
    }

    Rectangle
    {
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0)
        width: parent.width
        height: parent.height
        opacity: 0

        // Animates opacity change
        Behavior on opacity {
            NumberAnimation {
                easing.type: Easing.InOutCubic
                duration: root.panelAnimationSpeed
            }
        }
    }

    Rectangle
    {
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0)
        width: parent.width
        height: parent.height
        opacity: 0

        // Animates opacity change
        Behavior on opacity {
            NumberAnimation {
                easing.type: Easing.InOutCubic
                duration: root.panelAnimationSpeed
            }
        }
    }

    Rectangle
    {
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0)
        width: parent.width
        height: parent.height
        opacity: 0

        // Animates opacity change
        Behavior on opacity {
            NumberAnimation {
                easing.type: Easing.InOutCubic
                duration: root.panelAnimationSpeed
            }
        }
    }

    Rectangle
    {
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0)
        width: parent.width
        height: parent.height
        opacity: 0

        // Animates opacity change
        Behavior on opacity {
            NumberAnimation {
                easing.type: Easing.InOutCubic
                duration: root.panelAnimationSpeed
            }
        }
    }

    Rectangle
    {
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0)
        width: parent.width
        height: parent.height
        opacity: 0

        // Animates opacity change
        Behavior on opacity {
            NumberAnimation {
                easing.type: Easing.InOutCubic
                duration: root.panelAnimationSpeed
            }
        }
    }

    Rectangle
    {
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0)
        width: parent.width
        height: parent.height
        opacity: 0

        // Animates opacity change
        Behavior on opacity {
            NumberAnimation {
                easing.type: Easing.InOutCubic
                duration: root.panelAnimationSpeed
            }
        }
    }

    Rectangle
    {
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0)
        width: parent.width
        height: parent.height
        opacity: 0

        // Animates opacity change
        Behavior on opacity {
            NumberAnimation {
                easing.type: Easing.InOutCubic
                duration: root.panelAnimationSpeed
            }
        }
    }

    Rectangle
    {
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0)
        width: parent.width
        height: parent.height
        opacity: 0

        // Animates opacity change
        Behavior on opacity {
            NumberAnimation {
                easing.type: Easing.InOutCubic
                duration: root.panelAnimationSpeed
            }
        }
    }

    Rectangle
    {
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0)
        width: parent.width
        height: parent.height
        opacity: 0

        // Animates opacity change
        Behavior on opacity {
            NumberAnimation {
                easing.type: Easing.InOutCubic
                duration: root.panelAnimationSpeed
            }
        }
    }

    Rectangle
    {
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0)
        width: parent.width
        height: parent.height
        opacity: 0

        // Animates opacity change
        Behavior on opacity {
            NumberAnimation {
                easing.type: Easing.InOutCubic
                duration: root.panelAnimationSpeed
            }
        }
    }

    Rectangle
    {
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0)
        width: parent.width
        height: parent.height
        opacity: 0

        // Animates opacity change
        Behavior on opacity {
            NumberAnimation {
                easing.type: Easing.InOutCubic
                duration: root.panelAnimationSpeed
            }
        }
    }

    Rectangle
    {
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0)
        width: parent.width
        height: parent.height
        opacity: 0

        // Animates opacity change
        Behavior on opacity {
            NumberAnimation {
                easing.type: Easing.InOutCubic
                duration: root.panelAnimationSpeed
            }
        }
    }

    Rectangle
    {
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0)
        width: parent.width
        height: parent.height
        opacity: 0

        // Animates opacity change
        Behavior on opacity {
            NumberAnimation {
                easing.type: Easing.InOutCubic
                duration: root.panelAnimationSpeed
            }
        }
    }

    Rectangle
    {
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1.0)
        width: parent.width
        height: parent.height
        opacity: 0

        // Animates opacity change
        Behavior on opacity {
            NumberAnimation {
                easing.type: Easing.InOutCubic
                duration: root.panelAnimationSpeed
            }
        }
    }
}
