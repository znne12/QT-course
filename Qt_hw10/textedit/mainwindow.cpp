#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mdiArea = new QMdiArea(this);
    mdiArea->setGeometry(0, 56, 800, 510);
    mdiArea->setBackground(Qt::transparent);
    mdiArea->setViewMode(QMdiArea::TabbedView);
    mdiArea->setTabsClosable(true);
    textEdit = new ruTextEdit(mdiArea);
    QMdiSubWindow *activSubWindow = mdiArea->addSubWindow(textEdit);
    activSubWindow->resize(800, 480);
    activSubWindow->setWindowTitle(tr("Без имени"));
    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(changeTextEditPointer(QMdiSubWindow*)));
    styleCheckBox = new QCheckBox(tr("Ночной режим"), this);
    styleCheckBox->setGeometry(frameGeometry().width() - styleCheckBox->sizeHint().width(), styleCheckBox->sizeHint().height() + 10,
                               styleCheckBox->sizeHint().width(), styleCheckBox->sizeHint().height());

    filter = tr("Текстовый файл(*.txt);;Двоичный файл(*.original)");
    QFile fileAbout(":/res/about.txt");
    if (fileAbout.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fileAbout);
        about = stream.readAll();
        fileAbout.close();
    }
    file = new fileWork();

    connect(file, SIGNAL(returnOpenedText(QString, bool)), this,
                     SLOT(slot_textEdit_insertOpenedText(QString, bool)));
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

QStringList MainWindow::splitTextIntoParagraphs(QString strIn)
{
    QChar *list = strIn.data();
    QStringList strlst;
    int cursor = 0;
    for (bool getst = true;getst;)
    {
        int index = strIn.indexOf("\n", cursor); // Ищем перевод каретки
        // на новую строку
        QString s = "";
        if (index == -1)
        {
            getst = false;
            s.append(&list[cursor], strIn.length() - cursor);
        }
        else s.append(&list[cursor], index - cursor);
        cursor = index + 1;
        strlst << s;
    }
    return strlst;
}

ruTextEdit &MainWindow::getTextEdit()
{
    return *textEdit;
}

QAction &MainWindow::getQAction()
{
    return *ui->action_6;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    mdiArea->closeAllSubWindows();
}

void MainWindow::slot_textEdit_insertOpenedText(QString str, bool html)
{
    if(html){
        textEdit->setHtml(str);
    }else {
        textEdit->setText(str);
    }

}

void MainWindow::slot_authorEdit_insertAuthor(QString str)
{
    ui->authorEdit->setText(str);
    textEdit->authorText = str;
}


void MainWindow::on_action_undo_triggered()
{
    textEdit->undo();
}

void MainWindow::on_action_redo_triggered()
{
    textEdit->redo();
}

void MainWindow::on_action_about_triggered()
{
    aboutBox.setText(about);
    aboutBox.exec();
}


void MainWindow::on_action_open_triggered()
{
    textEdit=new ruTextEdit(mdiArea);
    QMdiSubWindow *sub = mdiArea->addSubWindow(textEdit,Qt::Window);
    sub->show();
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(textChangedInWindow()));

    ui->statusbar->clearMessage();
    ui->authorEdit->clear();
    textEdit->setReadOnly(false);
    QString s = QFileDialog::getOpenFileName(this, tr("Заголовок окна"), QDir::current().path(), filter);
    if (s.length() > 0)
        if(!file->openFile(s)) {
            aboutBox.setText(tr("Ошибка открытия файла!"));
            aboutBox.exec();
            return;
        }
    sub->widget()->setWindowTitle(s.right(s.size()-s.lastIndexOf("/")-1));
}

void MainWindow::on_action_save_triggered()
{
    QString s = QFileDialog::getSaveFileName(this, "Сохранить как", QDir::current().path(), filter);
    if(!s.indexOf(".txt")){
        if (s.length() > 0) if(!file->saveFile(s, textEdit->toHtml(), ui->authorEdit->text())) {
            aboutBox.setText(tr("Ошибка сохранения файла!"));
            aboutBox.exec();
        }
    }else{
        if (s.length() > 0) if(!file->saveFile(s, textEdit->toPlainText(), ui->authorEdit->text())) {
            aboutBox.setText(tr("Ошибка сохранения файла!"));
            aboutBox.exec();
        }
    }
        textEdit->setWindowTitle(s.right(s.size()-s.lastIndexOf("/")-1));
}

void MainWindow::on_action_openReadOnly_triggered()
{
    textEdit=new ruTextEdit(mdiArea);
    QMdiSubWindow *sub = mdiArea->addSubWindow(textEdit,Qt::Window);
    sub->show();
    QString s = QFileDialog::getOpenFileName(this, tr("Заголовок окна"), QDir::current().path(), filter);
    if (s.length() > 0)
        if(!file->openFile(s)) {
            aboutBox.setText(tr("Ошибка открытия файла!"));
            aboutBox.exec();
        }
    textEdit->setReadOnly(true);
    ui->statusbar->showMessage(tr("Открыто только для чтения"));
    sub->widget()->setWindowTitle(s.right(s.size()-s.lastIndexOf("/")-1));
}

void MainWindow::on_action_new_triggered()
{
    textEdit=new ruTextEdit(mdiArea);
    QMdiSubWindow *sub = mdiArea->addSubWindow(textEdit,Qt::Window);
    sub->widget()->setWindowTitle(tr("Без имени"));
    sub->show();
    ui->statusbar->clearMessage();
    ui->authorEdit->clear();
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

    qApp->exit();
}

void MainWindow::on_styleCheckBox_clicked()
{
    if (styleCheckBox->isChecked())  {
        qApp->setStyleSheet("QMenu{color: white; background-color: grey}"
                            "QMdiArea{color: white; background-color: grey}"
                            "QMenu::item:selected {background: #a8a8a8;}"
                            "QMainWindow{background-color:grey}"
                            "QCheckBox, ruTextEdit, QLabel, QLineEdit{color: white; background-color: grey}"
                            "ruTextEdit::cursor{color: red}"
                            "QMenuBar{background: transparent;border-radius: 4px;}"
                            "QMenuBar::item:selected {background: #a8a8a8;}"
                            "QToolBar::item:selected {background: #a8a8a8;}");

    } else {
        qApp->setStyleSheet("");

    }
}

void MainWindow::changeTextEditPointer(QMdiSubWindow *window)
{
    if(mdiArea->activeSubWindow()){
        textEdit = dynamic_cast<ruTextEdit*>(window->widget());
        ui->authorEdit->setText(textEdit->authorText);
    }
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    qint32 line = 0;
    QStringList strLst = splitTextIntoParagraphs(textEdit->toPlainText());
    QPrintDialog dlg(&printer, this);
    dlg.setWindowTitle("Print");
    if (dlg.exec() != QDialog::Accepted)
        return;
    //  textEdit->print(&printer);
    QPainter painter(this);
    painter.begin(&printer);
    int w = painter.window().width();
    int h = painter.window().height();
    int amount = strLst.count();
    QFont font = painter.font();
    QFontMetrics fmetrics(font);
    for (int i = 0; i < amount; i++)
    {
        QPointF pf;
        pf.setX(50);
        pf.setY(line+50);
        if (QSize(fmetrics.size(Qt::TextSingleLine ,strLst.at(i))).width() > w - 100){
            QString tmp = strLst.at(i);
            QString toPrint;
            do {
                do{
                    toPrint += tmp[0];
                    tmp.remove(0, 1);
                } while (QSize(fmetrics.size(Qt::TextSingleLine ,toPrint)).width() < w - 100 && tmp != "");
                pf.setY(line+50);
                painter.drawText(pf, toPrint);
                toPrint.clear();
                line += fmetrics.height();
            } while (tmp.length() != 0);
        }else {
            painter.drawText(pf, strLst.at(i));
        }
        line += fmetrics.height();
        if (h - line - 50 <= fmetrics.height())
        {
            printer.newPage();
            line = 0;
        }

    }
    painter.end();
}

void MainWindow::on_action_4_triggered()
{
    textEdit->setAlignment(Qt::AlignLeft);
}

void MainWindow::on_action_5_triggered()
{
    textEdit->setAlignment(Qt::AlignHCenter);
}

void MainWindow::on_action_6_triggered()
{
    textEdit->setAlignment(Qt::AlignRight);
}
