import QtQuick 2.0
import QtQuick.Window 2.14
import QtLocation 5.6
import QtPositioning 5.6


MapQuickItem {
    id: item
    property string name;
    property var lat
    property var lon
    anchorPoint.x: image.width/2
    anchorPoint.y: image.height/2
    coordinate: QtPositioning.coordinate(lat, lon)

    zoomLevel: 13.1

    sourceItem: Image{
        id: image

        source: "BS.png"
        height: 10
        width: 10
    }
}
