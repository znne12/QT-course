#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

class Model : public QSqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(QString query READ queryStr WRITE setQueryStr NOTIFY queryStrChanged)
    Q_PROPERTY(QStringList userRoleNames READ userRoleNames CONSTANT)

public:
    Model();
    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const override;
    QString queryStr() const{ return query().lastQuery(); }
    void setQueryStr(const QString &query);
    QStringList userRoleNames() const;
    Q_INVOKABLE void addTask(QString task, QString description, QString beginDate, QString endDate, quint32 progress);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QSqlQuery* query1;
signals:
    void queryStrChanged();

};

#endif // MODEL_H
