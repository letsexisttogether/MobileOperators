import QtQuick
import QtQuick.Controls

Dialog
{
    title: "Operator Editor"
    modal: true
    standardButtons: Dialog.Save | Dialog.Cancel

    contentItem: Column
    {
        spacing: 10
        TextField
        {
            id: nameField
            placeholderText: "Назва"
        }
        TextField
        {
            id: codeField
            placeholderText: "Код"
        }

    }

    onAccepted: console.log("Save pressed")
    onRejected: console.log("Cancel pressed")

    closePolicy: console.log(nameField.text, codeField.text)
}
