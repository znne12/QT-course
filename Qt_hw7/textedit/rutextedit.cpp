#include "rutextedit.h"
#include <QApplication>
#include <QClipboard>
#include <QDebug>
#include <QScrollBar>
#include <QPainter>
#include <QAbstractTextDocumentLayout>

ruTextEdit::ruTextEdit(QWidget *parent) : QTextEdit(parent)
{
    menu = new QMenu(this);
    QAction *copyAction = menu->addAction(tr("Копировать"));
    QAction *pastAction = menu->addAction(tr("Вставить"));
    QAction *separators = menu->addAction(tr("Добавить разделитель <hr>"));
    QAction *tables = menu->addAction(tr("Добавить таблицу"));
    QAction *selectFont = menu->addAction(tr("Выбрать шрифт"));
    QAction *copyFormat = menu->addAction(tr("Скопировать формат текста"));
    QAction *pasteFormat = menu->addAction(tr("Применить скопированный формат текста"));
    QAction *changeAlignment = menu->addAction(tr("Изменить выравнивание"));

    connect(copyAction, SIGNAL(triggered()), this, SLOT(copyText()));
    connect(pastAction, SIGNAL(triggered()), this, SLOT(pastText()));
    connect(separators, SIGNAL(triggered()), this, SLOT(addSeparators()));
    connect(selectFont, SIGNAL(triggered()), this, SLOT(addSelectedFont()));
    connect(tables, SIGNAL(triggered()), this, SLOT(addTable()));
    connect(copyFormat, SIGNAL(triggered()), this, SLOT(copyFormat()));
    connect(pasteFormat, SIGNAL(triggered()), this, SLOT(pasteFormat()));
    connect(changeAlignment, SIGNAL(triggered()), this, SLOT(changeAlignment()));

    filter = tr("Текстовый файл(*.txt);;Двоичный файл(*.original)");
    connect(this, &ruTextEdit::textChanged, this, &ruTextEdit::textIsChanged);
    lineNumberArea = new LineNumberArea(this);

    connect(this->document(), SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(updateLineNumberArea(int)));
    connect(this, SIGNAL(textChanged()), this, SLOT(updateLineNumberArea()));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(updateLineNumberArea()));

        updateLineNumberAreaWidth(0);
}
int ruTextEdit::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, this->document()->blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 13 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void ruTextEdit::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}


void ruTextEdit::updateLineNumberArea(QRectF /*rect_f*/)
{
    ruTextEdit::updateLineNumberArea();
}
void ruTextEdit::updateLineNumberArea(int /*slider_pos*/)
{
    ruTextEdit::updateLineNumberArea();
}

void ruTextEdit::updateLineNumberArea()
{
    /*
     * When the signal is emitted, the sliderPosition has been adjusted according to the action,
     * but the value has not yet been propagated (meaning the valueChanged() signal was not yet emitted),
     * and the visual display has not been updated. In slots connected to this signal you can thus safely
     * adjust any action by calling setSliderPosition() yourself, based on both the action and the
     * slider value.
     */
    // Make sure the sliderPosition triggers one last time the valueChanged() signal with the actual value !!!!
    this->verticalScrollBar()->setSliderPosition(this->verticalScrollBar()->sliderPosition());

    // Since "QTextEdit" does not have an "updateRequest(...)" signal, we chose
    // to grab the imformations from "sliderPosition()" and "contentsRect()".
    // See the necessary connections used (Class constructor implementation part).

    QRect rect =  this->contentsRect();
    lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
    updateLineNumberAreaWidth(0);
    //----------
    int dy = this->verticalScrollBar()->sliderPosition();
    if (dy > -1) {
        lineNumberArea->scroll(0, dy);
    }

    // Addjust slider to alway see the number of the currently being edited line...
    int first_block_id = getFirstVisibleBlockId();
    if (first_block_id == 0 || this->textCursor().block().blockNumber() == first_block_id-1)
        this->verticalScrollBar()->setSliderPosition(dy-this->document()->documentMargin());

//    // Snap to first line (TODO...)
//    if (first_block_id > 0)
//    {
//        int slider_pos = this->verticalScrollBar()->sliderPosition();
//        int prev_block_height = (int) this->document()->documentLayout()->blockBoundingRect(this->document()->findBlockByNumber(first_block_id-1)).height();
//        if (dy <= this->document()->documentMargin() + prev_block_height)
//            this->verticalScrollBar()->setSliderPosition(slider_pos - (this->document()->documentMargin() + prev_block_height));
//    }

}

void ruTextEdit::resizeEvent(QResizeEvent *e)
{
    QTextEdit::resizeEvent(e);

    QRect cr = this->contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

int ruTextEdit::getFirstVisibleBlockId()
{
    // Detect the first block for which bounding rect - once translated
    // in absolute coordinated - is contained by the editor text area

    // Costly way of doing but since "blockBoundingGeometry(...)" doesn't
    // exists for "QTextEdit"...

    QTextCursor curs = QTextCursor(this->document());
    curs.movePosition(QTextCursor::Start);
    for(int i=0; i < this->document()->blockCount(); ++i)
    {
        QTextBlock block = curs.block();

        QRect r1 = this->viewport()->geometry();
        QRect r2 = this->document()->documentLayout()->blockBoundingRect(block).translated(
                    this->viewport()->geometry().x(), this->viewport()->geometry().y() - (
                        this->verticalScrollBar()->sliderPosition()
                        ) ).toRect();

        if (r1.contains(r2, true)) { return i; }

        curs.movePosition(QTextCursor::NextBlock);
    }

    return 0;
}
void ruTextEdit::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    this->verticalScrollBar()->setSliderPosition(this->verticalScrollBar()->sliderPosition());

    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);
    int blockNumber = this->getFirstVisibleBlockId();

    QTextBlock block = this->document()->findBlockByNumber(blockNumber);
    QTextBlock prev_block = (blockNumber > 0) ? this->document()->findBlockByNumber(blockNumber-1) : block;
    int translate_y = (blockNumber > 0) ? -this->verticalScrollBar()->sliderPosition() : 0;

    int top = this->viewport()->geometry().top();

    // Adjust text position according to the previous "non entirely visible" block
    // if applicable. Also takes in consideration the document margin offset.
    int additional_margin;
    if (blockNumber == 0)
        // Simply adjust to document margin
        additional_margin = (int) this->document()->documentMargin() -1 - this->verticalScrollBar()->sliderPosition();
    else
        // Getting the height of the visible part of the previous "non entirely visible" block
        additional_margin = (int) this->document()->documentLayout()->blockBoundingRect(prev_block).translated(0, translate_y).intersected(this->viewport()->geometry()).height();

    // Shift the starting point
    top += additional_margin;

    int bottom = top + (int) this->document()->documentLayout()->blockBoundingRect(block).height();

    QColor col_1(90, 255, 30);      // Current line (custom green)
    QColor col_0(120, 120, 120);    // Other lines  (custom darkgrey)

    // Draw the numbers (displaying the current line number in green)
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen((this->textCursor().blockNumber() == blockNumber) ? col_1 : col_0);
            painter.drawText(-5, top,
                             lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) this->document()->documentLayout()->blockBoundingRect(block).height();
        ++blockNumber;
    }

}

void ruTextEdit::contextMenuEvent(QContextMenuEvent *event)
{
    menu->exec(event->globalPos());                 // Размещаем контекстное меню по экранным координатам
}

void ruTextEdit::closeEvent(QCloseEvent *event)
{
    if (needToSaveMessage()){
            saveWhenClosing();
       }
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
    this->textCursor().insertHtml("<hr>");
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

void ruTextEdit::addSelectedFont()
{
    bool ok;
    QFont newFont = QFontDialog::getFont(&ok);
    if (ok){
        QTextCharFormat fmt;
        fmt.setFont(newFont);
        textCursor().setCharFormat(fmt);
    }
}

void ruTextEdit::textIsChanged()
{
    isChanged = true;
}

void ruTextEdit::copyFormat()
{
    fmt_clipboard = textCursor().charFormat();
}

void ruTextEdit::pasteFormat()
{
    textCursor().setCharFormat(fmt_clipboard);
}

void ruTextEdit::changeAlignment()
{
    if(curAllig == Qt::AlignLeft){
        curAllig = Qt::AlignHCenter;
        setAlignment(curAllig);
    } else if(curAllig == Qt::AlignHCenter){
        curAllig = Qt::AlignRight;
        setAlignment(curAllig);
    }else if(curAllig == Qt::AlignRight){
        curAllig = Qt::AlignLeft;
        setAlignment(curAllig);
    }

}

bool ruTextEdit::needToSaveMessage()
{
    if (isChanged){
        QMessageBox save;
        save.setText(tr("Документ ")+ windowTitle() + tr(" был изменен!"));
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
    return false;
}

void ruTextEdit::saveWhenClosing()
{
    QString s = QFileDialog::getSaveFileName(this, "Сохранить как", QDir::current().path(), filter);
    if(!s.indexOf(".txt")){
        if (s.length() > 0) if(!file->saveFile(s, toHtml(), authorText)) {
            warningBox.setText(tr("Ошибка сохранения файла!"));
            warningBox.exec();
        }
    }else{
        if (s.length() > 0) if(!file->saveFile(s, toPlainText(), authorText)) {
            warningBox.setText(tr("Ошибка сохранения файла!"));
            warningBox.exec();
        }
    }
    setWindowTitle(s.right(s.size()-s.lastIndexOf("/")-1));
    isChanged = false;
}
