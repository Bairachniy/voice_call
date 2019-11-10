import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.4
import QtQuick.Dialogs 1.3

Rectangle {
    id:element

    color: "green"
    x: 0
    y: 0
    Rectangle{
         id: usersListPanel
         width: 0
         height: parent.height
         color: "#3f5b7a"
        ListView {
            Component.onCompleted: {
                usersModel.clear()
                usersListPanel.width = 100
                console.log(controller.getUsers())
                var arr = JSON.parse(controller.getUsers())
                for ( var i in arr ) {
                    usersModel.append( arr[i] );
                }

            }
            id: usersList
            anchors.fill: parent
            currentIndex:-1
            model:ListModel {
                id:usersModel
            }



            delegate: Component {
                Item {
                    width: parent.width
                    height: 100
                    Text {
                        padding: 5
                        width: parent.width
                        horizontalAlignment: Text.AlignLeft
                        font.pixelSize: 14
                        color: "white"
                        font.bold: true
                        text: usersModel.get(index).name
                        elide: Text.ElideRight


                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked:{
                            usersList.currentIndex = index
                            userDataPanel.visible = true
                            nameVal.text = usersModel.get(index).name
                            adressVal.text = usersModel.get(index).adress

                        }
                    }

                }



            }
            highlight: Rectangle {
                color: "lightsteelblue"
                radius: 2
            }
            highlightMoveDuration: 0
            highlightResizeDuration: 0
        }
    }

    Rectangle {
        id: userDataPanel
        color: "#233243"
        anchors.left: usersListPanel.right
        height: parent.height
        width: parent.width - usersListPanel.width
        visible: false
        Text {
            id: nameLb
            x: 13
            y: 23
            width: 58
            height: 30
            text: qsTr("Имя:")
            color: "white"
            font.bold: true
            horizontalAlignment: Text.AlignRight
            styleColor: "#000000"
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 12
        }

        Text {
            id: adressLb
            x: 13
            y: 59
            width: 58
            height: 25
            color: "white"
            font.bold: true
            text: qsTr("Адрес:")
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 12
        }

        Text {
            id: nameVal
            x: 102
            y: 23
            width: 155
            height: 23
            color: "white"
            font.bold: true
            text: qsTr("")
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 12
        }

        Text {
            id: adressVal
            x: 102
            y: 58
            width: 183
            height: 25
            color: "white"
            font.bold: true
            text: qsTr("")
            font.pixelSize: 12
        }

        RoundButton {
            id: callBtn
            x: 108
            y: 113
            width: 130

            background: Rectangle {
                id: btnRct
                        color: "#00cc66"
                        radius: parent.radius
                        Text{
                            color: "black"
                            font.bold: true
                        }
                    }
            height: 37
            text: qsTr("Позвонить")
            onClicked: {
                if(text == "Позвонить")
                {
                    btnRct.color = "#ff3333"
                    if(controller.call(nameVal.text, adressVal.text)){
                        text = qsTr("Завершить")
                        btnRct.color = "#ff3333"
                    }
                }
                else
                {
                    controller.disconnect()
                    text = qsTr("Позвонить")
                    btnRct.color = "#00cc66"
                }
            }
        }

    }

}





