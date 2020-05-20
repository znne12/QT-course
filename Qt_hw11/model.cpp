#include "model.h"
#include <QSqlError>

Model::Model()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./scheduler.db");
    if(!db.open()){
        qDebug() << "Cannot open database" << db.lastError().text();
    }
    QString str = "CREATE TABLE scheduler ("
                  "pos INTEGER PRIMARY KEY NOT NULL,"
                  "task VARCHAR(20),"
                  "description VARCHAR(50),"
                  "beginDate VARCHAR(10),"
                  "endDate VARCHAR(10),"
                  "progress INTEGER );";
    query1 = new QSqlQuery();
    if(!query1->exec(str)){
        qDebug() << "Unable to create a table!" << query1->lastError().text();
    }
}

QVariant Model::data(const QModelIndex &idx, int role) const
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

void Model::setQueryStr(const QString &query)
{
    if(queryStr() == query)
        return;
    setQuery(QSqlQuery(query));
    emit queryStrChanged();
}

QStringList Model::userRoleNames() const
{
    QStringList names;
    for (int i = 0; i < record().count(); i ++) {
        names << record().fieldName(i).toUtf8();
    }
    return names;
}

void Model::addTask(QString task, QString description, QString beginDate, QString endDate, quint32 progress)
{
    QString strAdd = "INSERT INTO scheduler (task, description, beginDate, endDate, progress)"
                     "VALUES('%1', '%2', '%3', '%4', '%5');";
    QString str = strAdd.arg(task).arg(description).arg(beginDate).arg(endDate).arg(progress);
    QSqlQuery quer;
    if(!quer.exec(str)){
        qDebug() << "Unable to add a task!";
    }
}

QHash<int, QByteArray> Model::roleNames() const
{
    QHash<int, QByteArray> roles;
    for (int i = 0; i < record().count(); i ++) {
        roles.insert(Qt::UserRole + i + 1, record().fieldName(i).toUtf8());
    }
    return roles;

}
