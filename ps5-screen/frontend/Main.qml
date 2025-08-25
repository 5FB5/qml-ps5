import QtQuick
import QtQuick.Controls
import QtQuick.Timeline
import "bootScreen"

ApplicationWindow
{
    id: root

    minimumWidth: 1600
    minimumHeight: 900
    visible: true
    title: qsTr("PS5 Screen")

    LabelStartupEpilepsy
    {
        id: labelStartupEpilepsy

        width: parent.width / 1.1
        height: parent.height / 1.5

        anchors.centerIn: parent

        animRunning: false

        font
        {
            capitalization: Font.AllUppercase
            family: "Ubuntu"
            pointSize: 20
            styleName: "Thin"
        }

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        opacity: 0
        scale: 1
        wrapMode: Text.WordWrap

        Timer
        {
            id: timerStartup

            interval: 1000
            repeat: false
            running: true

            onTriggered: function()
            {
                labelStartupEpilepsy.animRunning = true;
            }
        }
    }
}
