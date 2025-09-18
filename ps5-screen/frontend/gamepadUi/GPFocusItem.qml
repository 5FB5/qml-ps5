import QtQuick

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

    Rectangle {
        id: border

        anchors {
            fill: parent
            margins: -10
        }

        visible: root.focus && __debugMode
        color: "transparent"

        border {
            color: "tomato"
            width: 5
        }
    }
}
