import QtQuick
import QtQuick.Layouts

RowLayout
{
    Image
    {
        source: "file:///D:/Projects/MobileOperators/Resources/Countries/"
            + componentData.countryCode + ".png"
        width: 24
        height: 24
        fillMode: Image.PreserveAspectFit

        onStatusChanged:
        {
            if (status === Image.Error)
            {
                console.log(componentData.mcc)
            }
        }
    }

    Text { text: componentData.countryName }
    Text { text: componentData.countryCode }
    Text { text: componentData.mcc }
}
