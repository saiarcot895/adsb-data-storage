import QtQuick 2.2
import QtQuick.Controls 1.1

ApplicationWindow {
    visible: true
    width: 700
    height: 500
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
            width: positionTable.viewport.width
        }

        onClicked: {
            infoDisplay.reportingTime = model.data(row, "reportingTime");
            infoDisplay.messageType = model.data(row, "messageType");
            infoDisplay.latitude = model.data(row, "latitude");
            infoDisplay.longitude = model.data(row, "longitude");
            infoDisplay.altitude = model.data(row, "altitude");
        }
    }

    SplitView {
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.left: positionTable.right
        anchors.leftMargin: 6
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8

        Item {
            id: infoDisplay
            anchors.fill: parent

            property date reportingTime
            property string messageType
            property double latitude
            property double longitude
            property int altitude

            Label {
                id: reportingTimeLabel
                anchors.top: parent.top
                anchors.topMargin: 8
                anchors.left: parent.left
                anchors.leftMargin: 8
                text: "Reporting Time: "
            }

            Label {
                id: reportingTimeDisplay
                anchors.top: parent.top
                anchors.topMargin: 8
                anchors.left: reportingTimeLabel.right
                anchors.leftMargin: 6
                text: parent.reportingTime
            }

            Label {
                id: messageTypeLabel
                anchors.top: reportingTimeDisplay.bottom
                anchors.topMargin: 6
                anchors.left: parent.left
                anchors.leftMargin: 8
                text: "Message Type: "
            }

            Label {
                id: messageTypeDisplay
                anchors.top: reportingTimeDisplay.bottom
                anchors.topMargin: 6
                anchors.left: messageTypeLabel.right
                anchors.leftMargin: 6
                text: parent.messageType
            }

            Label {
                id: latitudeLabel
                anchors.top: messageTypeDisplay.bottom
                anchors.topMargin: 6
                anchors.left: parent.left
                anchors.leftMargin: 8
                text: "Latitude: "
            }

            Label {
                id: latitudeDisplay
                anchors.top: messageTypeDisplay.bottom
                anchors.topMargin: 6
                anchors.left: messageTypeLabel.right
                anchors.leftMargin: 6
                text: parent.latitude
            }

            Label {
                id: longitudeLabel
                anchors.top: latitudeDisplay.bottom
                anchors.topMargin: 6
                anchors.left: parent.left
                anchors.leftMargin: 8
                text: "Longitude: "
            }

            Label {
                id: longitudeDisplay
                anchors.top: latitudeDisplay.bottom
                anchors.topMargin: 6
                anchors.left: messageTypeLabel.right
                anchors.leftMargin: 6
                text: parent.longitude
            }

            Label {
                id: altitudeLabel
                anchors.top: longitudeDisplay.bottom
                anchors.topMargin: 6
                anchors.left: parent.left
                anchors.leftMargin: 8
                text: "Altitude: "
            }

            Label {
                id: altitudeDisplay
                anchors.top: longitudeDisplay.bottom
                anchors.topMargin: 6
                anchors.left: messageTypeLabel.right
                anchors.leftMargin: 6
                text: parent.altitude
            }
        }
    }
}
