#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTextDocument>
#include <QTranslator>
#include "filework.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void slot_plainTextEdit_insertOpenedText(QString str);

    void slot_authorEdit_insertAuthor(QString str);

    void on_action_undo_triggered();

    void on_plainTextEdit_textChanged();

    void on_action_redo_triggered();

    void on_action_about_triggered();

    void on_action_open_triggered();

    void on_action_save_triggered();

    void on_action_openReadOnly_triggered();

    void on_action_new_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_exit_triggered();

private:
    Ui::MainWindow *ui;
    QVector<std::pair <QString, quint32>> undoRedoStack;
    QVector<std::pair <QString, quint32>>::iterator ur_it;
    bool undoRedoFlag = false;
    quint32 prevPositionCursor = 0;
    QString filter;
    QMessageBox aboutBox;
    QString about;
    fileWork *file;
    bool isSaved;
    QTranslator translator;
    bool needToSaveMessage();
    void newStack();
};
#endif // MAINWINDOW_H
