import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "../Dialogs"
import "../Common"

RowLayout
{
    spacing: 16
    Layout.fillWidth: true

    ReliableImage
    {
        source: "file:///" + resourcesPath + "Countries/"
            + componentData.countryCode + ".png"
        width: 24
        height: 24
        fillMode: Image.PreserveAspectFit
    }

    Text { text: componentData.countryName }
    Text { text: componentData.countryCode }
    Text { text: componentData.mcc }

    Button
    {
        text: "+"

        width: 24
        height: 24

        onClicked: addDialog.open()
    }

    OperatorAddDialog
    {
        id: addDialog

        dialogData: componentData
    }
}
