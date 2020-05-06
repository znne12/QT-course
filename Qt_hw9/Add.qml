import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Window 2.3
Item {
    Rectangle{
        id:rect
        anchors.fill: parent
        color: '#eeee54'
    }
    Button
          {
              width: parent.width
              height: 30
              id: buttonAdd
              text: "Добавить задание"
              onClicked: {
                  var component = Qt.createComponent("NewData.qml")
                  console.log(component)
                  var obj = component.createObject(NewData)
                  console.log(obj)
                  obj.show()

              }
          }

    Label {
        id:l1
        text: "Позиция"
        x: 0
        y: 50
    }
    Label {
        id:l2
        text: "Задание"
        x: 51.67
        y: 50
    }
    Label {
        id:l3
        text: "Описание"
        x: 155
        y: 50
    }
    Label {
        id:l4
        text: "Дата начала"
        x: 361.66
        y: 50
    }
    Label {
        id:l5
        text: "Дата конца"
        x: 464.99
        y: 50
    }
    Label {
        id:l6
        text: "Прогресс"
        x: 568.32
        y: 50
    }
}
