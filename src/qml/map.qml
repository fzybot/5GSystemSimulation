import QtQuick 2.0
import QtQuick.Window 2.14
import QtLocation 5.6
import QtPositioning 5.6


// # up = 55.016656, 82.942833     down = 55.012888, 82.952097      center = 55.014619, 82.946997
Window {
    width: Qt.platform.os == "android" ? Screen.width : 1200
    height: Qt.platform.os == "android" ? Screen.height : 800
    visible: true

    Plugin {
        id: mapPlugin
        name: "osm" // "mapboxgl", "esri", ...
        // specify plugin parameters if necessary
        // PluginParameter {
        //     name:
        //     value:
        // }
    }

    Map {
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(55.014619, 82.946997) // Oslo
        zoomLevel: 16

        Rectangle {

            color: "#ff0000"
            width: 310
            height: 210
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (parent.color == "#ff0000") {
                        parent.color = "#ff9900";
                    } else {
                        parent.color = "#ff0000";
                    }
                }
            }
            Rectangle {
                width: 300
                height: 200
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Hello World"
                }
            }
        }
    }
}
