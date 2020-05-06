
import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import com.vv.filemanag 1.0

Window {
    id:root
    visible: true
    width: 640
    height: 480
    title: qsTr("scheduler!")

    property string sc: 'Element{width:620; height:150;' // Шаблон для
    // создания нового
    // компонента
    property string nc: 'Add{width:620; height:80;}'
    property int glPos: 0
    property int num: 0

    function addNewTask(pos, task, description, beginDate, endDate, progress)
    {
        loader.writeNewInformation(pos, task, description, beginDate, endDate, progress)
        var itog = sc + 'position:"' + pos + '";task:"' + task + '";description:"' + description + '";beginDate:"' + beginDate + '";endDate:"' + endDate + '";progress:"' + progress +'"}'
        var el = Qt.createQmlObject(itog, list, "obj" + num++)

    }
    Filemanag{
        id : loader
        onInitEnd:
        {
            if (succed)
            {
                var addButton = Qt.createQmlObject(nc, list, "objdata")
                loader.getNextRecord()
            } else Qt.quit()
        }
        onLoadTask: {
            glPos = pos;
            var itog = sc + 'position:"' + pos + '";task:"' + task + '";description:"' + description + '";beginDate:"' + beginDate + '";endDate:"' + endDate + '";progress:"' + progress +'"}'
            var el = Qt.createQmlObject(itog, list, "obj" + num++)
            loader.getNextRecord()
        }
    }
    ScrollView {
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        anchors.fill: parent       // Заполняем всю область родительского
        // объекта
        Component.onCompleted: loader.loadBase()
        ColumnLayout {
            id:list
            function add(pos, task, description, beginDate, endDate, progress) {
                root.addNewTask(pos, task, description, beginDate, endDate, progress)
                console.log(pos)
                console.log(task)
            }
        }
    }


}

