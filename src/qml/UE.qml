import QtQuick 2.0
import QtQuick.Window 2.14
import QtLocation 5.6
import QtPositioning 5.6


MapQuickItem {
    id: item
    property string name;
    property real lat
    property real lon
    property real moveToLat : lat
    property real moveToLon : lon
    anchorPoint.x: image.width/2
    anchorPoint.y: image.height/2
    coordinate: QtPositioning.coordinate(lat,lon)
    state:"idle"

    //zoomLevel: 1.1

    sourceItem: Grid{
        columns: 1
        Grid{
            Image{
                    id: image
                    visible: true
                    source: "UE.png"
                    height: 20
                    width: 20

                    MouseArea{
                        id : mouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                    }

                }
            Rectangle {
                id: bubble
                visible: mouseArea.containsMouse ? true : false
                color: "lightblue"
                border.width: 1
                width: text.width * 1.3
                height: text.height * 1.3
                radius: 5
                Text {
                    id: text
                    anchors.centerIn: parent
                    text: name
                }
            }
        }
    }

    states: [
        State {
            name: "moved"
            PropertyChanges {
                target: item
                lat:moveToLat
                lon:moveToLon

            }
        },
        State {
            name: "idle"
        }
    ]

    transitions: [
        Transition {
            from: "idle"
            to: "moved"
            NumberAnimation { properties: "lat,lon"; duration: 1000 }
        }
     ]

    Timer {
        interval: 10; running: true; repeat: true
        onTriggered:
        {
            if(item.state==="idle"){
                if(item.lat!==moveToLat || item.lon!==moveToLon){
                    item.state = "moved"
                }
            }
            if(item.state==="moved"){
                if(item.lat===moveToLat && item.lon===moveToLon){
                    item.state = "idle"
                    lat = moveToLat
                    lon = moveToLon
                }
            }
        }
    }

}
