#ifndef FILEWORK_H
#define FILEWORK_H
#include <QTextStream>
#include <QFileDialog>
#include <QObject>


class fileWork : public QObject{
    Q_OBJECT
private:

public:
    fileWork();
    bool openFile(QString s, bool forRead = false);
    bool saveFile(QString s, QString textToSave, QString authorStr);
signals:
    void returnOpenedText(QString str, bool html);
    void returnAuthor(QString str);
};

#endif // FILEWORK_H
