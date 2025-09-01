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
                color: buttonGames.checked ? "red" : "white"
                font {
                    family: "Ubuntu"
                    pointSize: 24
                    bold: buttonGames.checked
                }
            }

            checkable: true
            checked: false
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
                color: buttonMedia.checked ? "red" : "white"
                font {
                    family: "Ubuntu"
                    pointSize: 24
                    bold: buttonMedia.checked
                }
            }

            checkable: true
            checked: false
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
                width: 35
                height: 35
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
                width: 45
                height: 45
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
                width: 35
                height: 35
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
