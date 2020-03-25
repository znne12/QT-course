#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>

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
    void on_plainTextEdit_textChanged();

    void on_undoButton_clicked();

    void on_redoButton_clicked();

    void on_aboutButton_clicked();

    void on_saveButton_1_clicked();

    void on_openButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<QString> undoRedoStack;
    QVector<QString>::iterator ur_it;
    bool undoRedoFlag = false;
    QMessageBox aboutBox;
    QString about;
    QString fileName;
    QString filter;
};
#endif // MAINWINDOW_H
