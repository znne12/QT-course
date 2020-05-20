import QtQuick 2.12
import QtQuick.Controls 1.4
import sqlModel 1.0

TableView{
    id: tv1

    Model{
        id: sqlmodel
        query: "select * from scheduler"
    }
    TableViewColumn {
        role:"pos"
        title:"Позиция"
    }

    TableViewColumn {
        role:"task"
        title:"Задание"
    }

    TableViewColumn {
        role:"description"
        title:"Описание"
    }

    TableViewColumn {
        role:"beginDate"
        title:"Дата начала"
    }

    TableViewColumn {
        role:"endDate"
        title:"Дата окончания"
    }

    TableViewColumn {
        role:"progress"
        title:"Прогресс"
    }
    model: sqlmodel
}
