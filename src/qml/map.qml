import QtQuick 2.0
import QtQuick.Window 2.14
import QtLocation 5.6
import QtPositioning 5.6

Item {
    visible: true
    property int someNumber: 13
    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(55.012902, 82.950326) // Sibsutis
        zoomLevel: 14     

    }

    PositionSource {
        id: src
        updateInterval: 1
        active: true

        onPositionChanged: {
            console.log("Coordinate:", map.toCoordinate(Qt.point(0, 0)));
        }
    }

    MouseArea {
        visible: parent.containsDrag
        anchors.fill: parent

        property int lastX : -1
        property int lastY : -1

        onPressed : {
            lastX = mouse.x
            lastY = mouse.y
        }
        onPositionChanged: {
            map.pan(lastX - mouse.x, lastY - mouse.y)
            lastX = mouse.x
            lastY = mouse.y
        }
        onReleased: {
            console.log("Coordinate:", map.toCoordinate(Qt.point(0, 0)));
        }

    }

}
