#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "insertspecialchar.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->setViewMode(QListView::ListMode);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_plainTextEdit_textChanged()
{
    QString str = ui->plainTextEdit->toPlainText();
    bool addSpecSym = false;
    if (!str.contains("#@")) return;
    insertSpecialChar func;

    str = func.replaceSpecSyms(str, &addSpecSym);
    if (addSpecSym) {
        ui->plainTextEdit->setPlainText(str);
        ui->plainTextEdit->moveCursor(QTextCursor::End);
    }


}

void MainWindow::on_pushButton_clicked()
{
   QListWidgetItem *deft = new QListWidgetItem(QIcon(":/images/default.jpg"), "Default", ui->listWidget);

   deft->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);
   deft->setSelected(true);
}



void MainWindow::on_checkBox_clicked()
{
    if (ui->checkBox->isChecked()) ui->listWidget->setViewMode(QListView::IconMode);
    else ui->listWidget->setViewMode(QListView::ListMode);
}

void MainWindow::on_pushButton_2_clicked()
{
    delete ui->listWidget->currentItem();
}

void MainWindow::on_pushButton_4_clicked()
{
    int currentItemRow = ui->listWidget->currentRow();
    ui->listWidget->insertItem(currentItemRow + 1, ui->listWidget->takeItem(ui->listWidget->currentRow()));
    ui->listWidget->setCurrentRow(currentItemRow + 1);
}

void MainWindow::on_pushButton_3_clicked()
{
    int currentItemRow = ui->listWidget->currentRow();
    ui->listWidget->insertItem(currentItemRow - 1, ui->listWidget->takeItem(ui->listWidget->currentRow()));
    ui->listWidget->setCurrentRow(currentItemRow-1);
}

void MainWindow::on_pushButton_5_clicked()
{
    QList<QTableWidgetItem *> lst = ui->tableWidget->selectedItems();
    for (auto now : lst){
        now->setBackground(QBrush(QColor(0, 100, 0, 127), Qt::Dense1Pattern));
    }
}
