#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtMath"
#include "QThread"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_sqEq_clicked()
{
    if (ui->sq_a->text() == "") ui->sq_a->setText("0");
    if (ui->sq_b->text() == "") ui->sq_b->setText("0");
    if (ui->sq_c->text() == "") ui->sq_c->setText("0");
    qreal disc;
    bool err_input1, err_input2, err_input3;
    qreal a = ui->sq_a->text().toDouble(&err_input1);

    qreal b = ui->sq_b->text().toDouble(&err_input2);

    qreal c = ui->sq_c->text().toDouble(&err_input3);
    if (!err_input1 || !err_input2 || !err_input3) {
        ui->sq_x1->setText("Type int/double numbers plz");
        return;
    }
    disc = qPow(b, 2) - 4 * a * c;
    if (disc < 0) {
         ui->sq_x1->setText("The equation has no solutions");
    } else if (disc == 0) {
         ui->sq_x1->setText(QString :: number(-(b + qSqrt(disc)) / (2 * a), 'e'));
    } else if (a == 0) {
         ui->sq_x1->setText(QString :: number(c / b, 'e'));
    } else {
     ui->sq_x1->setText(QString :: number(-(b + qSqrt(disc)) / (2 * a), 'e'));
     ui->sq_x2->setText(QString :: number(-(b - qSqrt(disc)) / (2 * a), 'e'));
    }
}

void MainWindow::on_sq_a_textChanged(const QString &arg1)
{
    ui->sq_x1->clear();
    ui->sq_x2->clear();
}

void MainWindow::on_sq_b_textChanged(const QString &arg1)
{
    ui->sq_x1->clear();
    ui->sq_x2->clear();
}

void MainWindow::on_sq_c_textChanged(const QString &arg1)
{
    ui->sq_x1->clear();
    ui->sq_x2->clear();
}

void MainWindow::on_pushButton_degree_clicked()
{
    bool err_input1, err_input2, err_input3;
    qreal a = ui->triangle_a->text().toDouble(&err_input1);

    qreal b = ui->triangle_b->text().toDouble(&err_input2);

    qreal degree_ab = ui->triangle_degree_ab->text().toDouble(&err_input3);
    if (!err_input1 || !err_input2 || !err_input3) {
        ui->triangle_c->setText("Type int/double numbers plz");
        return;
    }
    if (ui->radioButton_degrees->isChecked()) {
        degree_ab = qDegreesToRadians(degree_ab);
    }
    qreal c = qSqrt(qPow(a, 2) + qPow(b, 2) - 2 * a * b * qCos(degree_ab));
    ui->triangle_c->setText(QString :: number(c));
}

void MainWindow::on_triangle_a_textChanged(const QString &arg1)
{
    ui->triangle_c->clear();
}

void MainWindow::on_triangle_b_textChanged(const QString &arg1)
{
    ui->triangle_c->clear();
}

void MainWindow::on_triangle_degree_ab_textChanged(const QString &arg1)
{
    ui->triangle_c->clear();
}

void MainWindow::on_pushButton_addText_clicked()
{
    ui->plainTextEdit->insertPlainText(ui->lineEdit->text());
}

void MainWindow::on_pushButton_replaceText_clicked()
{
    ui->plainTextEdit->setPlainText(ui->lineEdit->text());
}

void MainWindow::on_pushButton_replaceText_2_clicked()
{
    ui->textEdit->setHtml(ui->lineEdit_html->text());
}

void MainWindow::on_textEdit_textChanged()
{
    ui->textEdit_2->setDocument(ui->textEdit->document());
}

void MainWindow::on_pushButton_clicked()
{

    ui->textEdit_3->setTextColor(Qt::red);
    ui->textEdit_3->insertPlainText("Hello Qt!");
    ui->textEdit_3->setTextColor(Qt::blue);
    ui->textEdit_3->setTextBackgroundColor(Qt::gray);
    ui->textEdit_3->insertPlainText("Hello Qt!");
    ui->textEdit_3->setFontItalic(true);
    ui->textEdit_3->setTextColor(Qt::green);
    ui->textEdit_3->insertPlainText("Hello Qt!");
}
