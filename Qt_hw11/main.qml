import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import sqlModel 1.0

Window {

    visible: true
    width: 960
    height: 768
    title: qsTr("Scheduler")
    Model{
        id: sqlmodel
        query: ""
    }
    Rectangle{
        id: rect1
        anchors.left: parent.left
        anchors.right: parent.right
        height: 24
        TextField {
            id: textField
            x: 160
            width: 160
            text: qsTr("")
            placeholderText: "Введите значение!"
        }
        TextField {
            id: textField1
            anchors.left: textField.right
            width: 160
            text: qsTr("")
            placeholderText: "Введите значение!"
        }
        TextField {
            id: textField2
            anchors.left: textField1.right
            width: 160
            text: qsTr("")
            placeholderText: "Введите значение!"
        }
        TextField {
            id: textField3
            anchors.left: textField2.right
            width: 160
            text: qsTr("")
            placeholderText: "Введите значение!"
        }
        TextField {
            id: textField4
            anchors.left: textField3.right
            width: 160
            text: qsTr("")
            placeholderText: "Введите значение!"
        }
    }
    Rectangle{
        id: rect2
        anchors.top: rect1.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 30
        Button
        {
            width: parent.width
            height: 30
            id: buttonAdd
            text: "Добавить задание"
            onClicked:       {
                if (textField4.text >= 0 && textField4.text <= 100 && textField4.length > 0) {
                    sqlmodel.addTask(textField.text, textField2.text, textField2.text, textField3.text, textField4.text)
                }
            }
        }
    }

    View{
        id: v1
        width: parent.width
        anchors.top:rect2.bottom
        height: parent.height -60
    }
}
