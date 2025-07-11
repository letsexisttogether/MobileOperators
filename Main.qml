import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

import "UI/TreeElements"

ApplicationWindow
{
    width: 600
    height: 400
    visible: true
    title: qsTr("MobileOperators")

    TreeView
    {
        id: treeView

        anchors.fill: parent
        model: combinedModel

        ScrollBar.vertical: ScrollBar
        {
            policy: ScrollBar.AlwaysOn
        }

        delegate: TreeViewDelegate
        {
            id: delegate
            contentItem: Loader
            {
                sourceComponent:
                {
                    switch (model.level)
                    {
                        case 0: return country;
                        case 1: return operator;
                    }
                }

                property var componentData: model
            }
        }

        Component
        {
            id: country
            CountryComponent{}
        }

        Component
        {
            id: operator
            OperatorComponent{}
        }
    }

    Dialog
    {
        id: addOperatorDialog

        title: "Operator insertion"
        modal: true
        standardButtons: Dialog.Save | Dialog.Cancel

        contentItem: Column
        {
            spacing: 10
            TextField
            {
                id: name
                placeholderText: "Назва"
            }
            TextField
            {
                id: mcc
                placeholderText: "Код країни"
            }
            TextField
            {
                id: mnc
                placeholderText: "Код оператора"
            }
        }

        onAccepted: insertController.InsertOperator(name.text,
            parseInt(mnc.text), parseInt(mcc.text))
    }
}
