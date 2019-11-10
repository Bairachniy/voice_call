import QtQuick 2.13
import QtQuick.Controls 2.13

ApplicationWindow {

    id: _root
    visible: true
    width: 640
    height: 480
    title: qsTr("Voice Call")

    menuBar: MenuBar {
        id:bar
        visible: false
        Menu {
            id: mainMenu
            title: qsTr("&Меню")
            Action {
                text:qsTr("&Подключиться")

                }

        }
    }

    Rectangle{
       anchors.fill: parent

        Loader{
            anchors.fill: parent
            id: loader
            source: "login.qml";


        }
    }

    function openCabinet(){
        loader.source = "cabinet.qml"

    }
    function callWait(){
        loader.source = "call_wait.qml"

    }
    function showCall(){
        loader.source = "incoming_call.qml"
    }

}
