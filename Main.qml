import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

ApplicationWindow
{
    width: 600
    height: 400
    visible: true
    title: qsTr("Simple TreeView")

    TreeView {
        anchors.fill: parent
        model: combinedModel

        delegate: RowLayout {
            spacing: 10

            Text {
                text: model.level === 0
                      ? model.countryName + " (" + model.countryCode + ")"
                      : "  → " + model.operatorName + " (MNC: " + model.mnc + ")"
            }
        }
    }
}
