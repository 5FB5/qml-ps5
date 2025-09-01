import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item
{
    id: root

    Behavior on opacity {
        NumberAnimation {
            easing.type: Easing.InOutCubic
            duration: 300
        }
    }

    RowLayout {
        id: rowLayout

        anchors.fill: parent
        spacing: 0

        Button {
            id: buttonGames

            property bool isAlreadyChecked: false

            Layout.preferredWidth: 120
            Layout.preferredHeight: 50

            background: Item {}
            contentItem: Text {
                text: "Games"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: "white" //buttonGames.checked ? "red" : "white"
                font {
                    family: "Ubuntu"
                    styleName: "Thin"
                    pointSize: 24
                    bold: buttonGames.checked
                }
            }

            checkable: true
            checked: true

            onCheckedChanged: function()
            {
                if (checked)
                {
                    buttonMedia.checkable = true;
                    buttonMedia.checked = false;
                }
            }

            onToggled: function()
            {
                checkable = false;
            }
        }

        Button {
            id: buttonMedia

            Layout.preferredWidth: 350
            Layout.preferredHeight: 50

            background: Item {}
            contentItem: Text {
                text: "Media"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: "white" //buttonMedia.checked ? "red" : "white"
                font {
                    family: "Ubuntu"
                    styleName: "Thin"
                    pointSize: 24
                    bold: buttonMedia.checked
                }
            }

            checkable: true
            checked: false

            onCheckedChanged: function()
            {
                if (checked)
                {
                    buttonGames.checkable = true;
                    buttonGames.checked = false;
                }
            }

            onToggled: function()
            {
                checkable = false;
            }
        }

        Item { Layout.fillWidth: true }

        Button {
            id: buttonSearch

            Layout.preferredWidth: 65
            Layout.preferredHeight: 65

            display: AbstractButton.IconOnly

            background: Rectangle {
                radius: parent.Layout.preferredWidth
                color: "transparent"
            }
            // contentItem: Text {
            //     // text: "Search"
            //     horizontalAlignment: Text.AlignHCenter
            //     verticalAlignment: Text.AlignVCenter
            //     color: buttonGames.checked ? "red" : "white"
            //     font {
            //         family: "Ubuntu"
            //         pointSize: 24
            //         bold: buttonGames.checked
            //     }
            // }

            icon {
                source: "qrc:/resources/icons/search.svg"
                width: 25
                height: 25
                color: "white"
            }
        }

        Item { Layout.preferredWidth: 50 }


        Button {
            id: buttonSettings

            Layout.preferredWidth: 65
            Layout.preferredHeight: 65

            display: AbstractButton.IconOnly

            background: Rectangle {
                radius: parent.Layout.preferredWidth
                color: "transparent"
            }
            // contentItem: Text {
            //     // text: "Search"
            //     horizontalAlignment: Text.AlignHCenter
            //     verticalAlignment: Text.AlignVCenter
            //     color: buttonGames.checked ? "red" : "white"
            //     font {
            //         family: "Ubuntu"
            //         pointSize: 27
            //         bold: buttonGames.checked
            //     }
            // }

            icon {
                source: "qrc:/resources/icons/settings.svg"
                width: 35
                height: 35
                color: "white"
            }
        }

        Item { Layout.preferredWidth: 50 }

        Button {
            id: buttonProfile

            Layout.preferredWidth: 65
            Layout.preferredHeight: 65

            display: AbstractButton.IconOnly

            background: Rectangle {
                radius: parent.Layout.preferredWidth
                color: "transparent"
            }
            // contentItem: Text {
            //     // text: "Search"
            //     horizontalAlignment: Text.AlignHCenter
            //     verticalAlignment: Text.AlignVCenter
            //     color: buttonGames.checked ? "red" : "white"
            //     font {
            //         family: "Ubuntu"
            //         pointSize: 24
            //         bold: buttonGames.checked
            //     }
            // }

            icon {
                source: "qrc:/resources/icons/profile.svg"
                width: 25
                height: 25
                color: "white"
            }
        }

        Text {
            id: labelTime

            Layout.preferredWidth: 300
            Layout.preferredHeight: 75

            font
            {
                family: "Ubuntu"
                styleName: "Thin"
                pointSize: 30
            }
            color: "white"

            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter

            text: "11:19 AM"
        }
    }
}
