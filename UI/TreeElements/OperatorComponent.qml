import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "../Dialogs"
import "../Common"

RowLayout
{
    Image
    {
        source: "file:///" + resourcesPath + "Operators/"
            + componentData.mcc + "_" + componentData.mnc + ".png"
        width: 24
        height: 24
        fillMode: Image.PreserveAspectFit
    }

    Text
    {
        text: componentData.operatorName + " ("
            + componentData.mnc + ")"
    }

    Button
    {
        text: "+"
        font.pixelSize: 18

        width: 32
        height: 32

        onClicked:
        {
            if (!dialogLoader.active)
            {
                dialogLoader.active = true
            }
        }
    }
    Button
    {
        text: "-"

        font.pixelSize: 18

        width: 32
        height: 32

        onClicked: combinedModel.RemoveOperator(componentData.mcc,
            componentData.mnc)
    }

    Loader
    {
        id: dialogLoader

        active: false
        source: "../Dialogs/OperatorEditDialog.qml"
        visible: item !== null
        onLoaded:
        {
            item.dialogData = componentData
            item.open()
            item.onAccepted.connect(() => dialogLoader.active = false)
            item.onRejected.connect(() => dialogLoader.active = false)
        }
    }
}
