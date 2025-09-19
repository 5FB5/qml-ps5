import QtQuick
import QtQuick.Controls

import gamepadmanager

Item
{
    id: root

    required property GPFocusItem firstObject
    property GPFocusItem __lastObject: firstObject

    property bool lockFocus: false

    property bool debugMode: false

    function move(actionName) {
        if (!visible)
            return;

        switch(actionName) {
        case "up": {
            let topNeighbour = __lastObject.neighbours.top;
            if (topNeighbour === null || lockFocus)
                break;

            topNeighbour.focus = true;
            __lastObject = topNeighbour;
            break;
        }
        case "down": {
            let bottomNeighbour = __lastObject.neighbours.bottom;
            if (bottomNeighbour === null || lockFocus)
                break;

            bottomNeighbour.focus = true;
            __lastObject = bottomNeighbour;
            break;
        }
        case "left": {
            let leftNeighbour = __lastObject.neighbours.left;
            if (leftNeighbour === null || lockFocus)
                break;

            leftNeighbour.focus = true;
            __lastObject = leftNeighbour;
            break;
        }
        case "right": {
            let rightNeighbour = __lastObject.neighbours.right;
            if (rightNeighbour === null || lockFocus)
                break;

            rightNeighbour.focus = true;
            __lastObject = rightNeighbour;
            break;
        }
        default: break;
        }
    }

    function __handlerActionPressed(name) {
        if (!visible || !__lastObject.focus)
            return;

        __lastObject.actionPressed(name);
    }

    function __handlerActionReleased(name) {
        if (!visible || !__lastObject.focus)
            return;

        __lastObject.actionReleased(name);
    }

    function __setDebugMode() {
        for (let i = 0; i < children.length; i++) {
            let obj = children[i];

            if (!(obj instanceof GPFocusItem))
                continue;

            obj.__debugMode = debugMode;
        }
    }

    Component.onCompleted: function() {
        gamepadManager.actionPressed.connect(move);
        gamepadManager.actionPressed.connect(__handlerActionPressed);
        gamepadManager.actionReleased.connect(__handlerActionReleased);

        // firstObject.forceActiveFocus();

        __setDebugMode();
    }

    onDebugModeChanged: function() {
        __setDebugMode();
    }

    Rectangle {
        id: border

        parent: Overlay.overlay

        anchors {
            fill: parent
        }

        visible: debugMode
        color: "blue"
        opacity: 0.4
    }
}
