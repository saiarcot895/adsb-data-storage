import QtQuick 2.2
import QtQuick.Controls 1.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    TableView {
        id: aircraftTable
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        sortIndicatorVisible: true
        model: aircraftModel

        onSortIndicatorColumnChanged: model.sort(sortIndicatorColumn, sortIndicatorOrder)
        onSortIndicatorOrderChanged: model.sort(sortIndicatorColumn, sortIndicatorOrder)

        TableViewColumn {
            role: "hexCode";
            title: "Hex Code";
            width: 70
            delegate: Label {
                text: {
                    var hex = styleData.value.toString(16).toUpperCase();
                    var padding = 6;
                    while (hex.length < padding) {
                        hex = "0" + hex;
                    }
                    return hex;
                }
            }
        }

        TableViewColumn {
            role: "positionCount";
            title: "Position Count";
            width: 100
            delegate: Label {
                text: styleData.value
            }
        }

        onClicked: {
            mainWindow.displayAircraftHistory(row);
        }
    }

    TableView {
        id: positionTable
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.left: aircraftTable.right
        anchors.leftMargin: 6
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        model: positionModel

        TableViewColumn {
            role: "reportingTime";
            title: "Time";
            width: 70
        }
    }
}
