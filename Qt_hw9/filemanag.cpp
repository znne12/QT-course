#include "filemanag.h"
#include <QDataStream>

Filemanag::Filemanag() : file(nullptr)

{

}

Filemanag::~Filemanag()
{
     if (file) file->close();
}

void Filemanag::loadBase()
{
    file = new QFile("./schedulebase.bin", this);                 // Файл с данными
                                                                 // о городах
       if (!file) return;
       if (!file->open(QIODevice::ReadWrite))
       {
               emit initEnd(false);
               return;
       }
       emit initEnd(true);

}

void Filemanag::getNextRecord()
{
    if (file->atEnd()) return;
      QDataStream stream(file);
      int len = 0;
      stream.readRawData((char*)&len, sizeof len);
      QByteArray b;
      b.resize(len);
      stream.readRawData(b.data(), len);
      QString pos = QString::fromUtf8(b);

      stream.readRawData((char*)&len, sizeof len);
      b.resize(len);
      stream.readRawData(b.data(), len);
      QString task = QString::fromUtf8(b);

      stream.readRawData((char*)&len, sizeof len);
      b.resize(len);
      stream.readRawData(b.data(), len);
      QString description = QString::fromUtf8(b);

      stream.readRawData((char*)&len, sizeof len);
      b.resize(len);
      stream.readRawData(b.data(), len);
      QString beginDate = QString::fromUtf8(b);

      stream.readRawData((char*)&len, sizeof len);
      b.resize(len);
      stream.readRawData(b.data(), len);
      QString endDate = QString::fromUtf8(b);

      stream.readRawData((char*)&len, sizeof len);
      b.resize(len);
      stream.readRawData(b.data(), len);
      QString progress = QString::fromUtf8(b);

      emit loadTask(pos, task, description, beginDate, endDate, progress);

}

void Filemanag::writeNewInformation(QString pos, QString task, QString description, QString beginDate, QString endDate, QString progress)
{
    QDataStream stream(file);
    auto bytes = pos.toUtf8();
    int len = bytes.length();
    stream.writeRawData((char*)&len, sizeof len);
    stream.writeRawData(bytes.data(), len);
    bytes = task.toUtf8();
    len = bytes.length();
    stream.writeRawData((char*)&len, sizeof len);
    stream.writeRawData(bytes.data(), len);
    bytes = description.toUtf8();
    len = bytes.length();
    stream.writeRawData((char*)&len, sizeof len);
    stream.writeRawData(bytes.data(), len);
    bytes = beginDate.toUtf8();
    len = bytes.length();
    stream.writeRawData((char*)&len, sizeof len);
    stream.writeRawData(bytes.data(), len);
    bytes = endDate.toUtf8();
    len = bytes.length();
    stream.writeRawData((char*)&len, sizeof len);
    stream.writeRawData(bytes.data(), len);
    bytes = progress.toUtf8();
    len = bytes.length();
    stream.writeRawData((char*)&len, sizeof len);
    stream.writeRawData(bytes.data(), len);
}
