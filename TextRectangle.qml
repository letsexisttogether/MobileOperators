import QtQuick
import QtQuick.Controls

Rectangle
{
    width: 70
    height: 50
    anchors.centerIn: parent.Center

    border.color: "black"
    border.width: 2

    Text
    {
        text: modelData
        font.pointSize: 20
    }

    MouseArea
    {
        anchors.fill: parent

        onClicked:
        {
            parent.width = ((parent.width === 70) ? (140) : (70))
        }
    }
}
