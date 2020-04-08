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

class filemanagerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit filemanagerWidget(QWidget *parent = nullptr);
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
   private slots:
      void chgDisk(int index); // получаем индекс выбранного диска
      void goMainPath();       // Для UNIX-подобных ОС верхним уровнем является путь /
      void chgPath();
      void chgPathIndex(const QModelIndex &index);
   private:
      QStandardItemModel *model;
      QString currentPath;
   protected:

};

#endif // FILEMANAGERWIDGET_H
