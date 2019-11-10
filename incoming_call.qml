import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    color: "#103445"
    anchors.fill: parent

    Text {
        id: nameLb
        x: 279
        y: 151
        width: 83
        height: 26
        color: "white"
        font.bold: true
        text: "Text"
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 12
    }

    RoundButton{

        background: Rectangle {

                    color: "#29e386"
                    radius: parent.radius
                    Text{
                        id: okBtn
                        color: "white"
                        font.bold: true
                        font.pixelSize: 12
                    }
                }
        x: 212
        y: 250
        text:"Ответить"
        onClicked: {
            controller.acceptCall()
        }
    }
    RoundButton{
        background: Rectangle {

                    color: "#e82845"
                    radius: parent.radius
                    Text{
                        color: "white"
                        font.bold: true
                        font.pixelSize: 12
                    }
                }
        x: 361
        y: 250
        text:"Отклонить"
        onClicked:{
            controller.callDismised()
        }
    }


}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
