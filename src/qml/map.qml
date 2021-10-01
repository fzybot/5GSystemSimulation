import QtQuick 2.0
import QtQuick.Window 2.14
import QtLocation 5.6
import QtPositioning 5.6


Item {
    visible: true

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

        MapQuickItem {
            id: item

            anchorPoint.x: image.width/2
            anchorPoint.y: image.height/2
            coordinate: QtPositioning.coordinate(55.012902, 82.950326)

            zoomLevel: 13.1

            sourceItem: Image{
                id: image
                //color: "red"
                source: "BS.png"
                height: 10
                width: 10
            }
        }

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
