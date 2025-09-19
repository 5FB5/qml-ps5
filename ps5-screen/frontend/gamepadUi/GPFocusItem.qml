import QtQuick
import QtQuick.Controls

Item {
    id: root

    component Neighbours : QtObject {
        property GPFocusItem top
        property GPFocusItem bottom
        property GPFocusItem left
        property GPFocusItem right
    }

    property Neighbours neighbours : Neighbours {}

    property bool __debugMode: false

    signal actionPressed(string actionName)
    signal actionReleased(string actionName)

    Rectangle {
        id: border

        parent: Overlay.overlay

        width: root.width
        height: root.height

        x: root.x
        y: root.y

        visible: root.focus && __debugMode
        color: "tomato"
        opacity: 0.5
    }
}
