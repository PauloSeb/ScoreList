import QtQuick 2.0
Rectangle {
    id: mainWindow
    width: 800
    height: 600
    ListView {
         id: listView
         anchors.centerIn: parent
         anchors.fill: parent
         model: listModelC
         delegate: listDelegate
         highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
         focus: true
         section.property: "name"
         section.criteria: ViewSection.FullString
         section.delegate: headerDelegate
    }

    //Delegate for items
    Component {
             id: listDelegate
             Item {
                 width: 800
                 height: 40
                 Column {
                     Text { text: '<b>Category:</b> ' + category; color: mouseArea.containsMouse ? "red" : "black" }
                     Text { text: '<b>Id:</b> ' + number; color: mouseArea.containsMouse ? "red" : "black" }
                 }
                 MouseArea {
                    id: mouseArea
                    z: 1
                    hoverEnabled: true
                    anchors.fill: parent
                    onClicked:{
                        listView.currentIndex = index
                    }
                 }
             }
         }

    //Delegate for headers
    Component {
             id: headerDelegate
             Rectangle {
                 width: 800
                 height: 20
                 color: "lightgray"
                 radius: 5
                 Text {
                     text: section
                     font.bold: true
                 }
             }
         }
}
