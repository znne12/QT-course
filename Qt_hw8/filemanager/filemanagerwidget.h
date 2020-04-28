#ifndef FILEMANAGERWIDGET_H
#define FILEMANAGERWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QTreeView>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include <QApplication>
#include <QTimer>
#include <threadfinder.h>
#include <QPlainTextEdit>
#include <QSharedPointer>

class filemanagerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit filemanagerWidget(QWidget *parent = nullptr);
    ~filemanagerWidget();
    void clearTree();
      QStandardItemModel *getCurrentModel()const
      {
          return model;
      }
      void setNewModel(QStandardItemModel *newmodel);
      void rebuildModel(QString str);
   private:
      QGridLayout *gridLay;
      QTreeView *tree;
      QPushButton *mainPath;
      QComboBox *disckSelBox;
      QLineEdit *naviBar;
      QPlainTextEdit *textEdit;
      qint32 numsDiscsAtStart;
      QSharedPointer<ThreadFinder>  findThread;
   private slots:
      void chgDisk(int index); // получаем индекс выбранного диска
      void goMainPath();       // Для UNIX-подобных ОС верхним уровнем является путь /
      void chgPath();
      void chgPathIndex(const QModelIndex &index);
      void updateListDisks();
      void genStringPathFile(QString);
      void deleteThread();
   private:
      QStandardItemModel *model;
      QString currentPath;
   protected:

};

#endif // FILEMANAGERWIDGET_H
