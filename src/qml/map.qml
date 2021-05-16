import QtQuick 2.0
import QtQuick.Window 2.14
import QtLocation 5.6
import QtPositioning 5.6

Item {
    width: parent //Qt.platform.os == "android" ? Screen.width : 512
    height: parent //Qt.platform.os == "android" ? Screen.height : 512
    visible: true

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(55.012902, 82.950326) // Sibsutis
        zoomLevel: 14
    }
}
