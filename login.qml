import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        anchors.fill: parent
        color: "#c24a4a"

        Text {
            id: nameLb
            x: 113
            y: 164
            width: 71
            height: 26
            text: qsTr("Имя:")
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 12
        }

        Text {
            id: serverLb
            x: 113
            y: 202
            anchors.alignWhenCentered: parent
            width: 71
            height: 27
            text: qsTr("Сервер:")
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 12
        }
        Rectangle{
            x: 219
            y: 164
            width: 184
            height: 26
            color: "#721e1e"
            TextEdit {
                id: nameInp

                anchors.fill: parent
                text: qsTr("")
                font.pixelSize: 12
                onTextChanged: errorMsg.text = ""
            }

        }


        Rectangle{
            x: 219
            y: 203
            width: 184
            height: 26
            color: "#721e1e"
            TextEdit {
                id: serverInp
                anchors.fill: parent
                text: qsTr("")
                font.pixelSize: 12
                onTextChanged: errorMsg.text = ""
            }
        }

        Button{
            x: 229
            y: 285
            text: "Вход"
            onClicked: {
                var status = controller.logIn(nameInp.text, serverInp.text)
                console.log(status)
                switch(status)
                {
                case 1:
                    errorMsg.text = "Server is not available"
                    break
                }
            }
        }

        Text {
            id: errorMsg
            x: 212
            y: 246
            width: 191
            height: 28
            text: qsTr("")
            font.pixelSize: 12
        }

    }



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
