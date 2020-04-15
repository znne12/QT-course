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

class ruTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit ruTextEdit(QWidget *parent = nullptr);
    QString authorText;
protected:
    void contextMenuEvent(QContextMenuEvent *event) override; // Перехватим событие

signals:

public slots:
   void copyText();
   void pastText();
   void addSeparators();
   void addNumberingParagraphs();
   void addTable();
private:
   QMenu *menu;                                              // Для контекстного меню

};

#endif // RUTEXTEDIT_H
