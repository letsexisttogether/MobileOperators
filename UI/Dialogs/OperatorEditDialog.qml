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

                source: "file:///" + resourcesPath + "Operators/"
                    + dialogData.mcc + "_" + dialogData.mnc + ".png"

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
                id: nameField
                placeholderText: dialogData.operatorName
                Layout.fillWidth: true
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

            ReliableImage
            {
                source: "file:///" + resourcesPath + "Countries/"
                    + componentData.countryCode + ".png"
                width: 24
                height: 24
                fillMode: Image.PreserveAspectFit
                verticalAlignment: Image.AlignVCenter
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
            Text
            {
                text: dialogData.mnc
                font.pixelSize: 14
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    onAccepted: combinedModel.UpdateOperator(
        name.text, dialogData.mcc, dialogData.mnc)
}
