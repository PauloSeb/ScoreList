import QtQuick 2.0
Rectangle {
    id: mainWindow
    width: 360
    height: 360
    ListView {
         id: listView
         anchors.centerIn: parent
         anchors.fill: parent
         model: listModelC
         delegate: listDelegate
         highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
         focus: true
         section.property: "category"
         section.criteria: ViewSection.FullString
         section.delegate: headerDelegate
    }

    ListModel {
        id: listModel
         ListElement {
             name: "Bill Smith"
             category: "A"
             number: "555 3264"
         }
         ListElement {
             name: "John Brown"
             category: "A"
             number: "555 8426"
         }
         ListElement {
             name: "Sam Wise"
             category: "B"
             number: "555 0473"
         }
     }

    //Delegate for items
    Component {
             id: listDelegate
             Item {
                 width: 360
                 height: 60
                 Column {
                     Text { text: '<b>Name:</b> ' + name; color: mouseArea.containsMouse ? "red" : "black" }
                     Text { text: '<b>Category:</b> ' + category }
                     Text { text: '<b>Number:</b> ' + number }
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
                 width: 360
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
