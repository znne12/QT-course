#ifndef FILEMANAG_H
#define FILEMANAG_H

#include <QObject>
#include <QFile>
#include <QDate>

class Filemanag : public QObject
{
    Q_OBJECT
public:
   explicit Filemanag();
   virtual ~Filemanag();
   Q_INVOKABLE
   void loadBase();
   Q_INVOKABLE
   void getNextRecord();
   Q_INVOKABLE
   void writeNewInformation(QString pos, QString task, QString description, QString beginDate, QString endDate, QString progress);
private:
   QFile *file;
signals:
   void initEnd(bool succed);
   void loadTask(QString pos, QString task, QString description, QString beginDate, QString endDate, QString progress);
private slots:

};

#endif // FILEMANAG_H
