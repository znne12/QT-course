import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
    id:newData
    width: 640
    height: 480

    Text {
        id: element
        x: 15
        y: 36
        width: 63
        height: 14
        text: qsTr("Задание:")
        font.pixelSize: 12
    }

    Text {
        id: element1
        x: 15
        y: 91
        width: 63
        height: 14
        text: qsTr("Описание:")
        font.pixelSize: 12
    }

    Text {
        id: element2
        x: 15
        y: 149
        width: 69
        height: 14
        text: qsTr("Дата начала:")
        font.pixelSize: 12
    }

    Text {
        id: element3
        x: 15
        y: 207
        width: 86
        height: 14
        text: qsTr("Дата окончания:")
        font.pixelSize: 12
    }

    Text {
        id: element4
        x: 15
        y: 266
        width: 86
        height: 14
        text: qsTr("Прогресс:")
        font.pixelSize: 12
    }

    TextField {
        id: textField
        x: 125
        y: 23
        text: qsTr("")
        placeholderText: "Введите значение!"
    }

    TextField {
        id: textField1
        x: 125
        y: 78
        text: qsTr("")
        placeholderText: "Введите значение!"
    }

    TextField {
        id: textField2
        x: 125
        y: 136
        text: qsTr("")
        placeholderText: "Введите значение!"
    }

    TextField {
        id: textField3
        x: 125
        y: 194
        text: qsTr("")
        placeholderText: "Введите значение!"
    }

    TextField {
        id: textField4
        x: 125
        y: 253
        text: qsTr("")
        placeholderText: "Введите значение!"
    }

    Button {
        id: button
        x: 459
        y: 136
        text: qsTr("Добавить задание")
        onClicked:
        {
            if (textField4.text >= 0 && textField4.text <= 100 && textField4.length > 0) {
                var pos = ++glPos
                var task = textField.text
                var description = textField1.text
                var beginDate = textField2.text
                var endDate = textField3.text
                var progress = textField4.text
                list.add(pos, task, description, beginDate, endDate, progress)
            }
        }


    }
}
