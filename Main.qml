import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.qmlmodels

Window
{
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ListView
    {
        width: 500
        height: 500
        model: listModel

        anchors.centerIn: parent

        delegate: Column
        {
            Text { text: "Назва" + Name }
            Text { text: "Країна" + Mcc }
            Text { text: "Код" + Mnc }

            Image
            {
                width: 16
                height: 13
                fillMode: Image.PreserveAspectFit

                source: "file:///D:/Projects/MobileOperators/Resources/"
                    + Mcc + "_" + Mnc + ".png"
            }

            Rectangle
            {
                height: 1
                color: "gray"
                width: parent.width
            }
        }
    }

    /*
    OperatorDialog
    {
        id: myDialog
        anchors.centerIn: parent
    }

    Button
    {
        text: "Показати діалог"
        anchors.centerIn: parent
        onClicked: myDialog.open()
    }

    */
}
