#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_sqEq_clicked();

    void on_sq_a_textChanged(const QString &arg1);

    void on_sq_b_textChanged(const QString &arg1);

    void on_sq_c_textChanged(const QString &arg1);

    void on_pushButton_degree_clicked();

    void on_triangle_a_textChanged(const QString &arg1);

    void on_triangle_b_textChanged(const QString &arg1);

    void on_triangle_degree_ab_textChanged(const QString &arg1);

    void on_pushButton_addText_clicked();

    void on_pushButton_replaceText_clicked();

    void on_pushButton_replaceText_2_clicked();

    void on_textEdit_textChanged();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
