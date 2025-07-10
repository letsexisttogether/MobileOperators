import QtQuick
import QtQuick.Layouts

import "D:/Projects/MobileOperators/UI/Dialogs"

RowLayout
{
    Image
    {
        source: "file:///D:/Projects/MobileOperators/Resources/Operators/"
            + componentData.mcc + "_" + componentData.mnc + ".png"
        width: 24
        height: 24
        fillMode: Image.PreserveAspectFit

        onStateChanged:
        {
            // TODO: fix later
            if (status === Image.Error)
            {
                console.log(componentData.operatorName)
            }

        }
    }

    Text { text: componentData.operatorName }
    Text { text: componentData.mnc }
    Text { text: componentData.mcc }

    MouseArea
    {
        acceptedButtons: Qt.LeftButton
    }
}
