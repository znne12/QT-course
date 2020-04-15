#include "rutextedit.h"
#include <QApplication>
#include <QClipboard>
#include <QDebug>

ruTextEdit::ruTextEdit(QWidget *parent) : QTextEdit(parent)
{
    menu = new QMenu(this);
    QAction *copyAction = menu->addAction(tr("Копировать"));
    QAction *pastAction = menu->addAction(tr("Вставить"));
    QAction *separators = menu->addAction(tr("Добавить разделитель <hr>"));
    QAction *numberingParagraphs = menu->addAction(tr("Добавить нумерацию абзацев"));
    QAction *tables = menu->addAction(tr("Добавить таблицу"));
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copyText()));
    // Подключаем слот к сигналу
    connect(pastAction, SIGNAL(triggered()), this, SLOT(pastText()));
    connect(separators, SIGNAL(triggered()), this, SLOT(addSeparators()));
    connect(numberingParagraphs, SIGNAL(triggered()), this, SLOT(addNumberingParagraphs()));
    connect(tables, SIGNAL(triggered()), this, SLOT(addTable()));
}
void ruTextEdit::contextMenuEvent(QContextMenuEvent *event)
{
    menu->exec(event->globalPos());                 // Размещаем контекстное меню по экранным координатам
}



void ruTextEdit::copyText()
{
   QString str = this->textCursor().selectedText(); // Получаем выделенный текст
   qApp->clipboard()->setText(str);                 // Копируем текст
}
void ruTextEdit::pastText()
{
   QString str = qApp->clipboard()->text();          // Извлекаем из буфера
                                                     // обмена
   this->textCursor().insertText(str);               // Вставляем текст
   // в позицию курсора
}

void ruTextEdit::addSeparators()
{
    QString str = this->toPlainText();
    quint32 tmp = 0;
    for (int i = 0; i < str.count("\n") ; ++i){
        tmp = str.indexOf("\n", tmp);
        str = str.insert(tmp, "<hr>");
        tmp += 5;


    }
    this->setText(str);
}

void ruTextEdit::addNumberingParagraphs()
{
    QString str = this->toPlainText();
    quint32 tmp = 0;
    quint32 paragrNums = 1;
    str = str.insert(tmp , QString::number(paragrNums) + ". ");
    for (int i = 0; i < str.count("\n"); ++i){
        paragrNums++;
        tmp = str.indexOf("\n", tmp);
        str = str.insert(tmp + 1, QString::number(paragrNums) + ". ");
        tmp += QString::number(paragrNums).length();


    }
    this->setText(str);
}

void ruTextEdit::addTable()
{
    QDialog dlg(this);
    dlg.setWindowTitle(tr("Добавить таблицу"));

    QLineEdit *ledit1 = new QLineEdit(&dlg);
    QLineEdit *ledit2 = new QLineEdit(&dlg);

    QDialogButtonBox *btn_box = new QDialogButtonBox(&dlg);
    btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(btn_box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(btn_box, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

    QFormLayout *layout = new QFormLayout();
    layout->addRow(tr("Количество строк:"), ledit1);
    layout->addRow(tr("Количество колонок:"), ledit2);
    layout->addWidget(btn_box);
    dlg.setLayout(layout);
    if(dlg.exec() == QDialog::Accepted) {
        const QString &str1 = ledit1->text();
        const QString &str2 = ledit2->text();
        QTextTableFormat tableFormat;
        tableFormat.setWidth(340);
        this->textCursor().insertTable(str1.toInt(), str2.toInt(), tableFormat);
    }

}
