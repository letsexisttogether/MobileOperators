import QtQuick

Image
{
    id: image

    onStatusChanged:
    {
        if (image.status === Image.Error)
        {
            image.source = "file:///" + resourcesPath + "Icons/"
                + "QuestionMark.png"
        }
    }
}
