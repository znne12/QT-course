import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Item {
   id: rootItem
   property string  position: "P";
   property string  task: "";
   property string  description: "";
   property string  beginDate: "";
   property string  endDate: "";
   property string  progress: "";
   Rectangle{
       id:rect
       anchors.fill: parent
       color: '#eeeee4'
   }
   Component.onCompleted:
   {
       width = parent.width;
       height = 25

       positionText.width = parent.width / 12;
       taskText.width = parent.width / 6;
       descText.width = parent.width / 3;
       beginText.width = parent.width / 6;
       endText.width = parent.width / 6;
       progText.width = parent.width / 12;
       var p = 3;
       positionText.x = p;
       p += positionText.width
       taskText.x = p;
       p += taskText.width
       descText.x = p;
       p += descText.width
       beginText.x = p;
       p += beginText.width
       endText.x = p;
       p += endText.width
       progText.x = p;
   }
   Label {
       id:positionText
       text: position
       x: position.x;
   }

   Label {
       id:taskText
       text: task
       x: task.x;
   }
   Label {
       id:descText
       text: description
   }
   Label {
       id:beginText
       text: beginDate
   }
   Label {
       id:endText
       text: endDate
   }
   Label {
       id:progText
       text: progress
   }
}

