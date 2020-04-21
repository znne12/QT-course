#ifndef RUTEXTEDIT_H
#define RUTEXTEDIT_H

#include <QMainWindow>
#include <QObject>
#include <QTextEdit>
#include <QContextMenuEvent>
#include <QMenu>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QTextTableFormat>
#include <QMdiSubWindow>
#include <QMessageBox>
#include "filework.h"
#include <QTextList>
#include "linenumberarea.h"
#include <QFontDialog>

class ruTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit ruTextEdit(QWidget *parent = nullptr);
    int getFirstVisibleBlockId();
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    QString authorText;
protected:
    void contextMenuEvent(QContextMenuEvent *event) override; // Перехватим событие
    void closeEvent(QCloseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

signals:

public slots:
   void copyText();
   void pastText();
   void addSeparators();
   void addTable();
   void addSelectedFont();
   void textIsChanged();
   void copyFormat();
   void pasteFormat();
   void changeAlignment();
private:
   QMenu *menu;
   bool isChanged = false;
   bool needToSaveMessage();
   void saveWhenClosing();
   QMessageBox warningBox;
   fileWork *file;
   QString filter;
   QWidget *lineNumberArea;
   QTextCharFormat fmt_clipboard;
   Qt::AlignmentFlag curAllig = Qt::AlignLeft;
private slots:
   void updateLineNumberAreaWidth(int newBlockCount);
   void updateLineNumberArea(QRectF /*rect_f*/);
   void updateLineNumberArea(int /*slider_pos*/);
   void updateLineNumberArea();

};

#endif // RUTEXTEDIT_H
