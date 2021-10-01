import QtQuick 2.0
import QtQuick.Window 2.14
import QtLocation 5.6
import QtPositioning 5.6


MapQuickItem {
    id: item
    property string name;
    property var coordinates
    anchorPoint.x: image.width/2
    anchorPoint.y: image.height/2
    coordinate: coordinates

    zoomLevel: 13.1

    sourceItem: Image{
        id: image

        source: "BS.png"
        height: 10
        width: 10
    }
}
