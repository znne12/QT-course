#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    styleCheckBox = new QCheckBox(tr("Ночной режим"), this);
    styleCheckBox->setGeometry(frameGeometry().width() - styleCheckBox->sizeHint().width(), styleCheckBox->sizeHint().height() + 10,
                               styleCheckBox->sizeHint().width(), styleCheckBox->sizeHint().height());
    isSaved = true;

    undoRedoStack.push_front({ui->plainTextEdit->toPlainText(), ui->plainTextEdit->textCursor().position()});
    ur_it = undoRedoStack.begin();

    filter = tr("Текстовый файл(*.txt);;Двоичный файл(*.original)");
    QFile fileAbout(":/res/about.txt");
    if (fileAbout.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fileAbout);
        about = stream.readAll();
        fileAbout.close();
    }
    file = new fileWork();

    connect(file, SIGNAL(returnOpenedText(QString)), this,
                     SLOT(slot_plainTextEdit_insertOpenedText(QString)));
    connect(file, SIGNAL(returnAuthor(QString)), this,
                     SLOT(slot_authorEdit_insertAuthor(QString)));
    connect(styleCheckBox, SIGNAL(clicked()), this,
                     SLOT(on_styleCheckBox_clicked()));

    translator.load(":/Qt_hw4_ru_RU.qm");
}

MainWindow::~MainWindow()
{
    delete file;
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key::Key_F3){
        on_action_open_triggered();
    }
}

void MainWindow::slot_plainTextEdit_insertOpenedText(QString str)
{
    undoRedoFlag = true; //что бы isSaved не изменялся
    ui->plainTextEdit->setPlainText(str);
    undoRedoFlag = false;
}

void MainWindow::slot_authorEdit_insertAuthor(QString str)
{
    ui->authorEdit->setText(str);
}


void MainWindow::on_action_undo_triggered()
{
    if (undoRedoStack.size() > 0 && ur_it->first != undoRedoStack.last().first){
        undoRedoFlag = true;
        quint32 tmpPosCursor = ur_it->second;
        quint32 diffLengthStr = ur_it->first.length();
        ++ur_it;
        diffLengthStr -= ur_it->first.length(); // вычисляем разницу кол-ва символов строк
        ui->plainTextEdit->setPlainText(ur_it->first);
        undoRedoFlag = false;
        QTextCursor *newCursor = new QTextCursor(ui->plainTextEdit->document());
        newCursor->setPosition(tmpPosCursor-diffLengthStr);// изменяем позицию курсора
        ui->plainTextEdit->setTextCursor(*newCursor);
        delete newCursor;
    }
}

void MainWindow::on_plainTextEdit_textChanged()
{
    if (!undoRedoFlag){
        if (ur_it != undoRedoStack.begin()) undoRedoStack.erase(undoRedoStack.begin(), ur_it);
        undoRedoStack.push_front({ui->plainTextEdit->toPlainText(), ui->plainTextEdit->textCursor().position()});
        ur_it = undoRedoStack.begin();
        isSaved = false;
    }
}

void MainWindow::on_action_redo_triggered()
{
    if (ur_it != undoRedoStack.begin()){
        undoRedoFlag = true;
        --ur_it;
        ui->plainTextEdit->setPlainText(ur_it->first);
        undoRedoFlag = false;
        QTextCursor *newCursor = new QTextCursor(ui->plainTextEdit->document());
        newCursor->setPosition(ur_it->second);
        ui->plainTextEdit->setTextCursor(*newCursor);
        delete newCursor;
    }
}

void MainWindow::on_action_about_triggered()
{
    aboutBox.setText(about);
    aboutBox.exec();
}


void MainWindow::on_action_open_triggered()
{
    if (needToSaveMessage()){
        on_action_save_triggered();
    }
    ui->authorEdit->clear();
    ui->plainTextEdit->setReadOnly(false);
    QString s = QFileDialog::getOpenFileName(this, tr("Заголовок окна"), QDir::current().path(), filter);
    if (s.length() > 0)
        if(!file->openFile(s)) {
            aboutBox.setText(tr("Ошибка открытия файла!"));
            aboutBox.exec();
        }
    newStack();
}

void MainWindow::on_action_save_triggered()
{
    QString s = QFileDialog::getSaveFileName(this, "Сохранить как", QDir::current().path(), filter);
    if (s.length() > 0) if(!file->saveFile(s, ui->plainTextEdit->toPlainText(), ui->authorEdit->text())) {
        aboutBox.setText(tr("Ошибка сохранения файла!"));
        aboutBox.exec();
        isSaved = true;
    }
}

void MainWindow::on_action_openReadOnly_triggered()
{
    if (needToSaveMessage()){
        on_action_save_triggered();
    }
    ui->authorEdit->clear();
    QString s = QFileDialog::getOpenFileName(this, tr("Заголовок окна"), QDir::current().path(), filter);
    if (s.length() > 0)
        if(!file->openFile(s)) {
            aboutBox.setText(tr("Ошибка открытия файла!"));
            aboutBox.exec();
        }
    ui->plainTextEdit->setReadOnly(true);
    ui->statusbar->showMessage(tr("Открыто только для чтения"));
    newStack();
}

void MainWindow::on_action_new_triggered()
{
    if (needToSaveMessage()){
        on_action_save_triggered();
    }
    ui->plainTextEdit->setReadOnly(false);
    ui->plainTextEdit->clear();
    ui->statusbar->clearMessage();
    isSaved = true;
    newStack();
}

bool MainWindow::needToSaveMessage(){
    if (!isSaved){
        QMessageBox save;
        save.setText(tr("Документ был изменен!"));
        save.setInformativeText(tr("Вы хотите сохранить изменения?"));
        save.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
        save.setDefaultButton(QMessageBox::Save);
        int ret = save.exec();
        switch (ret) {
           case QMessageBox::Save:
               return true;
               break;
           case QMessageBox::Discard:
               return false;
               break;
           default:
               break;
         }
    }
}

void MainWindow::newStack()
{
    undoRedoStack.clear();
    undoRedoStack.push_front({ui->plainTextEdit->toPlainText(), ui->plainTextEdit->textCursor().position()});
    ur_it = undoRedoStack.begin();
}

void MainWindow::on_action_2_triggered()
{
    qApp->removeTranslator(&translator);
    ui->retranslateUi(this);
}

void MainWindow::on_action_3_triggered()
{

    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}

void MainWindow::on_action_exit_triggered()
{
    if (needToSaveMessage()){
        on_action_save_triggered();
    }
    qApp->exit();
}

void MainWindow::on_styleCheckBox_clicked()
{
    if (styleCheckBox->isChecked())  {
        qApp->setStyleSheet("QMenu{color: white; background-color: grey}"
                            "QMenu::item:selected {background: #a8a8a8;}"
                            "QMainWindow{background-color:grey}"
                            "QCheckBox, QPlainTextEdit, QLabel, QLineEdit{color: white; background-color: grey}"
                            "QPlainTextEdit::cursor{color: red}"
                            "QMenuBar{background: transparent;border-radius: 4px;}"
                            "QMenuBar::item:selected {background: #a8a8a8;}"
                            "QToolBar::item:selected {background: #a8a8a8;}");
    } else {
        qApp->setStyleSheet("");

    }
}
