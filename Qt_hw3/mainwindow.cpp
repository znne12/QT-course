#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    undoRedoStack.push_front(ui->plainTextEdit->toPlainText());
    ur_it = undoRedoStack.begin();
    filter = trUtf8("Текстовый файл(*.txt);;Двоичный файл(*.original)");

    QFile file(":/res/about.txt");
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        about = stream.readAll();
        file.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_plainTextEdit_textChanged()
{
    if (!undoRedoFlag){
        if (ur_it != undoRedoStack.begin()) undoRedoStack.erase(undoRedoStack.begin(), ur_it);
        undoRedoStack.push_front(ui->plainTextEdit->toPlainText());
        ur_it = undoRedoStack.begin();
    }
}

void MainWindow::on_undoButton_clicked()
{
    if (undoRedoStack.size() > 0 && ur_it != undoRedoStack.last()){
        undoRedoFlag = true;
        ui->plainTextEdit->setPlainText(*++ur_it);
        undoRedoFlag = false;
    }
}

void MainWindow::on_redoButton_clicked()
{
    if (ur_it != undoRedoStack.begin()){
        undoRedoFlag = true;
        ui->plainTextEdit->setPlainText(*--ur_it);
        undoRedoFlag = false;
    }
}

void MainWindow::on_aboutButton_clicked()
{
    aboutBox.setText(about);
    aboutBox.exec();
}

void MainWindow::on_saveButton_1_clicked()
{
    QString s = QFileDialog::getSaveFileName(this, "Сохранить как", QDir::current().path(), filter);
    if (s.length() > 0)
    {
        int index = s.indexOf(".txt"); // определяем, есть ли в названии
                                       // строка ".txt"
        QFile file(s);
        if (file.open(QFile::WriteOnly))
        {
            if (index != -1)           // если текстовый файл (выполняются
                                       // 2 условия)
            {
                QTextStream stream(&file);
                stream << ui->plainTextEdit->toPlainText();
            }
            else {
                QDataStream stream(&file);
                if (ui->authorEdit->text() == 0) {
                    QByteArray b = QString("GB_Qt_Auth0").toUtf8();
                    stream.writeRawData(b.data(), b.length());
                } else { // если автор есть, то после записи Magichead, записываем число символов в строке автора и самого автора
                    QByteArray b = QString("GB_Qt_Auth1").toUtf8();
                    QByteArray author = ui->authorEdit->text().toUtf8();
                    stream.writeRawData(b.data(), b.length());
                    uint amount = author.length();
                    stream.writeRawData(reinterpret_cast<char*>(&amount), sizeof amount);
                    stream.writeRawData(author.data(), amount);
                }
                QHash<QChar, int>symbamount;
                symbamount.clear();
                QString str = ui->plainTextEdit->toPlainText();
                int amount = str.length();
                QString usedS = "";
                for (int i = 0; i < amount; ++i) {
                    QChar ch = str.at(i);
                    int index = usedS.indexOf(ch);
                    if (index == -1)
                    {
                        symbamount[ch] = 0;
                        usedS += ch;
                    }
                    else{
                       symbamount[ch]++;
                    }
                }
                //********************************
                for (int i = 0; i < amount; ++i) {
                    QChar chi = usedS[i];
                    for (int j = i + 1; j < amount; ++j) {
                    QChar chj = usedS[j];
                        if (symbamount[chi] < symbamount[chj])
                        {
                            usedS[i] = chj;
                            usedS[j] = chi;
                            chi = chj;
                        }
                    }
                }
                symbamount.clear(); // больше не понадобится
                //**********************************************
                QByteArray b = usedS.toUtf8();
                amount = b.length();
                stream.writeRawData(reinterpret_cast<char*>(&amount), sizeof amount);
                stream.writeRawData(b.data(), amount);
                //***********************************************
                amount = str.length();
                for (int i = 0; i < amount; i++) {
                    int index = usedS.indexOf(str.at(i));
                    for (bool w = true; w;) {
                        char wr = index % 128;
                        index /= 128;
                        if (index) {
                            wr |= 0x80;
                            stream.writeRawData(&wr, 1); // старший бит
                                                         // сообщает, что
                                                         // значение состоит
                                                         // еще из 1 байта
                        }
                        else {
                            stream.writeRawData(&wr, 1);
                            w = false;
                        }
                    }
                }

            }
            file.close();
        }

    }
}



void MainWindow::on_openButton_clicked()
{
    ui->authorEdit->clear();
    QString s = QFileDialog::getOpenFileName(this, "Заголовок окна", QDir::current().path(), filter);
    if (s.length() > 0)
    {
        int index = s.indexOf(".txt");
        QFile file(s);
        if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
        {
            if (index != -1 && s.length() - 4 == index) // если текстовый файл
                                                        // (выполняются 2
                                                        // условия)
            {
                QTextStream stream(&file);
                ui->plainTextEdit->setPlainText(stream.readAll());
                ui->authorEdit->clear();
            }
            else
            {
                QDataStream stream(&file);
                QByteArray withAuthor = QString("GB_Qt_Auth1").toUtf8();
                QByteArray withoutAuthor = QString("GB_Qt_Auth0").toUtf8();
                char mH[15];
                stream.readRawData(mH, withAuthor.length());
                if (memcmp(mH, withAuthor.data(), withAuthor.length()) &
                    memcmp(mH, withoutAuthor.data(), withoutAuthor.length()))    // если не совпадает
                                                                                 // хотябы один из заголовков, то открытие
                                                                                 // недопустимо, так как
                                                                                 // формат у файла другой
                {
                    file.close();
                    return;
                }
                if (!memcmp(mH, withAuthor.data(), withAuthor.length())) { // если заголовок с автором, то считываем автора
                    uint amount = 0;
                    stream.readRawData(reinterpret_cast<char*>(&amount), sizeof amount);
                    withAuthor.resize(amount);
                    stream.readRawData(withAuthor.data(), amount);
                    ui->authorEdit->setText(trUtf8(withAuthor.data()));
                }
                uint amount = 0;
                stream.readRawData(reinterpret_cast<char*>(&amount), sizeof amount);
                withoutAuthor.resize(amount);
                stream.readRawData(withoutAuthor.data(), amount);
                QString usedS = trUtf8(withoutAuthor.data());
                QString str = "";
                uint pos = 0;
                uint mm = 1;
                for (;!stream.atEnd();) { // atEnd() true конец файла
                    char ch;
                    stream.readRawData(&ch, 1);
                    bool bl = (ch & 0x80) ? false : true;
                    int rValue = (ch & 0x7F);
                    pos += mm * rValue;
                    mm *= 128;
                    if (bl)
                    {
                        mm = 1;
                        str += usedS.at(pos);
                        pos = 0;
                    }
                }
                ui->plainTextEdit->setPlainText(str);
            }
        }
        file.seek(0);
        auto pp = file.readAll();
        file.close();
    }
}
