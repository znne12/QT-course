#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCheckBox>
#include <QTranslator>
#include "filework.h"
#include <QMdiArea>
#include <QMdiSubWindow>
#include <rutextedit.h>
#include <QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    QStringList splitTextIntoParagraphs(const QString strIn);
protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void slot_textEdit_insertOpenedText(QString str, bool html);

    void slot_authorEdit_insertAuthor(QString str);

    void on_action_undo_triggered();

    void on_action_redo_triggered();

    void on_action_about_triggered();

    void on_action_open_triggered();

    void on_action_save_triggered();

    void on_action_openReadOnly_triggered();

    void on_action_new_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_exit_triggered();

    void on_styleCheckBox_clicked();

    void changeTextEditPointer(QMdiSubWindow *window);

    void on_actionPrint_triggered();

    void on_action_4_triggered();

    void on_action_5_triggered();

    void on_action_6_triggered();

private:
    Ui::MainWindow *ui;
    QString filter;
    QMessageBox aboutBox;
    QString about;
    fileWork *file;
    QTranslator translator;
    QCheckBox *styleCheckBox;
    QMdiArea *mdiArea;
    ruTextEdit *textEdit;

};
#endif // MAINWINDOW_H
