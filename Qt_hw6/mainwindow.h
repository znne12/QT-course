#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCheckBox>
#include <QTranslator>
#include "filework.h"
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QTextEdit>
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

    void deleteSubWindow(QObject*);

    void textChangedInWindow();


    void on_actionPrint_triggered();

private:
    Ui::MainWindow *ui;
    QString filter;
    QMessageBox aboutBox;
    QString about;
    fileWork *file;
    QTranslator translator;
    bool needToSaveMessage(ruTextEdit *tmpTextEdit = nullptr);
    QCheckBox *styleCheckBox;
    QMdiArea *mdiArea;
    ruTextEdit *textEdit;
    QMap<ruTextEdit*, bool> isChangedWindow;
    void saveWhenClosing(ruTextEdit * tmpTextEdit);

};
#endif // MAINWINDOW_H
