#include "sqltables.h"
#include <QDebug>

SqlTables::SqlTables(QObject *parent) : QSqlTableModel(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./scheduler.db");
    if(!db.open()){
        qDebug() << "Cannot open database" << db.lastError().text();
        qApp->exit();
    }
    QString str = "CREATE TABLE scheduler ("
                  "pos INTEGER PRIMARY KEY NOT NULL,"
                  "task VARCHAR(20),"
                  "description VARCHAR(50),"
                  "beginDate VARCHAR(10),"
                  "endDate VARCHAR(10),"
                  "progress INTEGER );";
    qDebug() << str;
    query = new QSqlQuery(db);
    if(!query->exec(str)){
        qDebug() << "Unable to create a table!" << query->lastError().text();
    }
  //  model = new QSqlTableModel(this, db);
    setTable("scheduler");
    select();
    setEditStrategy(QSqlTableModel::EditStrategy::OnFieldChange);
    //model->insertRows(0, 1);
    //model->setData(model->index(0,1), "anna");
    //if(!model->submitAll()){ qDebug << "error";}
//    addTask("todo", "job", "19.05.2020", "20.05.2020", 87);

    qDebug() << rowCount();
    //qDebug() << model->data()
}

SqlTables::~SqlTables()
{

}

//int SqlTables::rowCount(const QModelIndex &parent) const
//{
//    Q_UNUSED(parent)
//    return static_cast<int>()
//}

QVariant SqlTables::data(const QModelIndex &idx, int role) const
{
    QVariant value;
          if (idx.isValid()) {
              if (role < Qt::UserRole) {
                  value = QSqlQueryModel::data(idx, role);
              } else {
                  int columnIdx = role - Qt::UserRole - 1;
                  QModelIndex modelIndex = this->index(idx.row(), columnIdx);
                  value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
              }
          }
          return value;
}

//void SqlTables::getTask(quint32 pos, QString &task, QString &description, QString &beginDate, QString &endDate, quint32 &progress)
//{
//    query.exec("SELECT * FROM scheduler");
//    QSqlRecord rec = query.record();
//    while(query.next()){
//        qDebug() << query.value(rec.indexOf("pos")).toInt() << " " <<
//                    query.value(rec.indexOf("task")).toString() << " " <<
//                    query.value(rec.indexOf("description")).toString() << " " <<
//                    query.value(rec.indexOf("progress")).toString() << " ";
//    }
//}

QHash<int, QByteArray> SqlTables::roleNames() const
{
    QHash<int, QByteArray> roles;
        roles[PosRole] = "pos";
        roles[TaskRole] = "task";
        roles[DescriptionRole] = "description";
        roles[BeginDateRole] = "beginDate";
        roles[EndDateRole] = "endDate";
        roles[ProgressRole] = "progress";
        return roles;
}

void SqlTables::addTask(QString task, QString description, QString beginDate, QString endDate, quint32 progress)
{
    QString strAdd = "INSERT INTO scheduler (task, description, beginDate, endDate, progress)"
                     "VALUES('%1', '%2', '%3', '%4', '%5');";
    QString str = strAdd.arg(task).arg(description).arg(beginDate).arg(endDate).arg(progress);
    if(!query->exec(strAdd)){
        qDebug() << "Unable to add a task!" << db.lastError().text();
    }
}

