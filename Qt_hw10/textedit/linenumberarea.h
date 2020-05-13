#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H
#include <QWidget>
#include "rutextedit.h"
class LineNumberArea : public QWidget
{
    Q_OBJECT
public:
    LineNumberArea(QTextEdit *editor);


    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QTextEdit *codeEditor;
};

#endif // LINENUMBERAREA_H
