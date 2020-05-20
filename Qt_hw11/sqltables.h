#ifndef SQLTABLES_H
#define SQLTABLES_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QGuiApplication>


class SqlTables : public QSqlTableModel
{
    Q_OBJECT

    enum Roles{
        PosRole = Qt::UserRole + 1,
        TaskRole,
        DescriptionRole,
        BeginDateRole,
        EndDateRole,
        ProgressRole
    };

public:
    explicit SqlTables(QObject *parent = nullptr);
    ~SqlTables();
   // int rowCount(const QModelIndex &parent = QModelIndex{}) const override;
   QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const override;

    void addTask(QString task, QString description, QString beginDate, QString endDate, quint32 progress);
   // void getTask(quint32 pos, QString& task, QString& description, QString& beginDate, QString& endDate, quint32& progress);

protected:
    QHash<int, QByteArray> roleNames() const override;


private:
    QSqlDatabase db;
    QSqlQuery *query;
 //   QSqlTableModel *model;

};

#endif // SQLTABLES_H
