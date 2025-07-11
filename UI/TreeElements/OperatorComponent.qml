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

    Text { text: componentData.operatorName }
    Text { text: componentData.mnc }
    Text { text: componentData.mcc }

    Button
    {
        text: "+"
        font.pixelSize: 18

        width: 32
        height: 32

        onClicked: operatorEditDialog.open()
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

    // TODO: Fix using Loader later
    OperatorEditDialog
    {
        id: operatorEditDialog
        dialogData: componentData
    }
}
