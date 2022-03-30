import QtQuick 2.0
import QtQuick.Window 2.2
import QtLocation 5.6
import QtPositioning 5.6
import QtGraphicalEffects 1.15

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

        MapItemView{
            model: _ueModel
            delegate: UE{
                name: model.name
                lat: model.lat
                lon: model.lon
                moveToLat: model.moveToLat
                moveToLon: model.moveToLon
            }
        }

            MapPolygon {
                id:polygon
                     color: '#55000000'
                     border.color: '#55000000'
                     path: [
                         { latitude: 55.009088, longitude: 82.933401 },
                         { latitude: 55.009088, longitude: 82.960240 },
                         { latitude: 55.018151, longitude: 82.960240 },
                         { latitude: 55.018151, longitude: 82.933401 }
                     ]
                     visible: false
            }

            Image {
                id: image
                source: ""
                visible: false
            }

            OpacityMask
            {
                source: image
                maskSource: polygon
                anchors.fill: polygon
            }
            //update image every sec
            Timer{
                interval: 1000; running: true; repeat: true;
                onTriggered: {
                    image.source=""
                    image.source=PixelMap
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
