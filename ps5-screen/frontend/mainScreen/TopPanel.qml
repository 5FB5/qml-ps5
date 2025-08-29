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

        anchors
        {
            fill: parent
            // margins: 20
            // leftMargin: 50
        }

        layoutDirection: Qt.LeftToRight
        uniformCellSizes: true
        spacing: -10

        Button {
            id: buttonGames

            property bool isAlreadyChecked: false

            implicitWidth: 100
            implicitHeight: 50

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

            implicitWidth: 200
            implicitHeight: 50

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

        Button {
            id: buttonSearch

            implicitWidth: 65
            implicitHeight: 65

            background: Rectangle {
                radius: implicitWidth
            }
            contentItem: Text {
                // text: "Search"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: buttonGames.checked ? "red" : "white"
                font {
                    family: "Ubuntu"
                    pointSize: 24
                    bold: buttonGames.checked
                }
            }
        }

        Button {
            id: buttonProfile

            implicitWidth: 65
            implicitHeight: 65

            background: Rectangle {
                radius: parent.Layout.preferredWidth
            }
            contentItem: Text {
                // text: "Search"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: buttonGames.checked ? "red" : "white"
                font {
                    family: "Ubuntu"
                    pointSize: 24
                    bold: buttonGames.checked
                }
            }
        }

        Button {
            id: buttonSettings

            implicitWidth: 65
            implicitHeight: 65

            background: Rectangle {
                radius: implicitWidth
            }
            contentItem: Text {
                // text: "Search"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: buttonGames.checked ? "red" : "white"
                font {
                    family: "Ubuntu"
                    pointSize: 27
                    bold: buttonGames.checked
                }
            }
        }

        Text {
            id: labelTime

            Layout.preferredWidth: 120
            Layout.preferredHeight: 75

            font
            {
                family: "Ubuntu"
                styleName: "Thin"
                pointSize: 26
            }

            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter

            text: "11:19 AM"
        }
    }
}
