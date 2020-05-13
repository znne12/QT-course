#include "linenumberarea.h"

LineNumberArea::LineNumberArea(QTextEdit *editor) : QWidget(editor)
{
    codeEditor = editor;
}

QSize LineNumberArea::sizeHint() const {
    return QSize(((ruTextEdit *)codeEditor)->lineNumberAreaWidth(), 0);
}

void LineNumberArea::paintEvent(QPaintEvent *event) {
    ((ruTextEdit *)codeEditor)->lineNumberAreaPaintEvent(event);
}
