#include "threadfinder.h"
#include <QDir>

ThreadFinder::ThreadFinder(QString dir, QString file, QObject *parent) : QThread (parent)
{
   this->dir = dir;
   this->file = file;
   toWork = true;
}

void ThreadFinder::run()
{
    QStringList dirs = {dir};

    QDir search(dirs.at(0));

    search.setFilter(QDir::Hidden | QDir::Files | QDir::NoSymLinks);
    QStringList foundFiles = search.entryList();
    int amount = foundFiles.count();
    for (int j = 0; j < amount && toWork; j++) // пока не просмотрены все
        // файлы или пока флаг
        // toWork не установлен в
        // false
    {
        QString filename = foundFiles.at(j);
        if (filename.indexOf(file) != -1)
        {
            emit findFile(dir + filename);
            emit stopedThread();
        }

    }
    emit stopedThread();                            // Сообщаем о завершении
    // работы потока
}
