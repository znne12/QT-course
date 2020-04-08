#include "filemanagerwidget.h"
#include <QDir>

filemanagerWidget::filemanagerWidget(QWidget *parent) : QWidget(parent), model(nullptr)
{
    gridLay = new QGridLayout(this);        // создаем слой для компоновки
      this->setLayout(gridLay);               // устанавливаем слой на виджет
      tree = new QTreeView(this);
      connect(tree, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(chgPathIndex(const QModelIndex)));
      gridLay->addWidget(tree, 1, 0, 10, 10); // размещен на первой строке
                                              // с нулевого столбца
                                              // занимает 10 условных строк
                                              // и столбцов
      setMinimumSize(500, 600);               // ограничиваем размер виджета

      if(QSysInfo::productType() == "windows")
      {
          disckSelBox = new QComboBox(this);
          QFileInfoList list = QDir::drives();
          QFileInfoList::const_iterator listdisk = list.begin();
          int amount = list.count();
          for (int i = 0; i < amount; i++)
          {
              disckSelBox->addItem(listdisk->path());
              listdisk++;
          }
          if (amount > 0)
          {
              rebuildModel(list.at(0).path());
          }
          gridLay->addWidget(disckSelBox, 0, 0, 1, 2); // координаты
          connect(disckSelBox, SIGNAL(activated(int)), this, SLOT(chgDisk(int)));
      } else {
          mainPath = new QPushButton(this);
          mainPath->setText("/");
          gridLay->addWidget(mainPath, 0, 0, 1, 2);
          connect(mainPath, SIGNAL(clicked()), this, SLOT(goMainPath()));
          rebuildModel("/");
      }
    naviBar = new QLineEdit(currentPath, this);
    gridLay->addWidget(naviBar, 0, 2, 1, 8);

    connect(naviBar, SIGNAL(returnPressed()), this, SLOT(chgPath()));

}

void filemanagerWidget::chgDisk(int index)
{
   QFileInfoList list = QDir::drives();
   rebuildModel(list.at(index).path());
}

void filemanagerWidget::goMainPath()
{
    rebuildModel("/");
}

void filemanagerWidget::chgPath()
{
    QDir dir(currentPath);
    if(dir.cd(naviBar->text())) rebuildModel(naviBar->text());
}

void filemanagerWidget::chgPathIndex(const QModelIndex &index)
{
    QDir dir(currentPath);
    if(model->itemFromIndex(index)->text() == "..") dir.cdUp();
    else if(model->itemFromIndex(index)->text() != '.')  dir.cd(model->itemFromIndex(index)->text());
    rebuildModel(dir.path());
naviBar->setText(currentPath);

}


void filemanagerWidget::setNewModel(QStandardItemModel *newmodel)
{
    tree->setModel(newmodel);
    model = newmodel;
}
void filemanagerWidget::rebuildModel(QString str)
{
   currentPath = str;
   //naviBar->setText("currentPath");
   QStandardItemModel *model = new QStandardItemModel;
   QList<QStandardItem*> items;
   items.append(new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DriveHDIcon)), str));
   model->appendRow(items);


   QDir dir(str);
   dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Dirs);
   QStringList list = dir.entryList();
   int amount = list.count();
   QList<QStandardItem*>folders;
   for (int i = 0; i < amount; i++)
   {
       QStandardItem* f = new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon)), list.at(i));
       folders.append(f);
   }

   items.at(0)->appendRows(folders);

   dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Files);
   list = dir.entryList();
   amount = list.count();
   QList<QStandardItem*>files;
   for (int i = 0; i < amount; i++)
   {
       QStandardItem* f = new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon)), list.at(i));
       files.append(f);
   }

   items.at(0)->appendRows(files);
   setNewModel(model);
   tree->expandAll();
}
