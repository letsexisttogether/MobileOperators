import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "../Common"

Dialog
{
    required property var dialogData;

    width: 250
    height: 150

    anchors.centerIn: parent
    modal: true
    standardButtons: Dialog.Save | Dialog.Cancel

    ColumnLayout
    {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 10

        RowLayout
        {
            spacing: 20

            ReliableImage
            {
                id: image

                width: 24
                height: 24
                fillMode: Image.PreserveAspectFit

                source: "file:///" + resourcesPath + "Countries/"
                    + componentData.countryCode + ".png"

                horizontalAlignment: Image.AlignHCenter
            }
            Label
            {
                text: "Edit Operator:"
                font.bold: true
                font.pixelSize: 20

                Layout.alignment: Qt.AlignVCenter
            }
        }

        RowLayout
        {
            spacing: 10
            Label
            {
                text: "NAME:"
                Layout.alignment: Qt.AlignVCenter
            }
            TextField
            {
                id: name
                placeholderText: "Name..."
                Layout.fillWidth: true
            }
        }
        RowLayout
        {
            spacing: 10
            Label
            {
                text: "MNC:"
                Layout.alignment: Qt.AlignVCenter
            }
            TextField
            {
                id: mnc
                placeholderText: "mnc..."
                Layout.fillWidth: true

                inputMethodHints: Qt.ImhDigitsOnly

                onTextChanged:
                {
                    var filtered = text.replace(/\D/g, "")
                    if (text !== filtered)
                    {
                        text = filtered
                    }

                    var val = parseInt(text)
                    if (!isNaN(val) && val > 2147483647)
                    {
                        text = "2147483647"
                    }
                }
            }
        }
        RowLayout
        {
            spacing: 10
            Label
            {
                text: "MCC:"
                Layout.alignment: Qt.AlignVCenter
            }
            Text
            {
                text: dialogData.mcc
                font.pixelSize: 14
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    onAccepted: combinedModel.AddOperator(
        name.text, dialogData.mcc, mnc.text)
}
