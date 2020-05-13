#include "unittest.h"
#include "mainwindow.h"
#include "rutextedit.h"
#include <QMenuBar>
#include <QPlainTextEdit>

UnitTest::UnitTest(QObject *parent)
{

}

void UnitTest::testGUI()
{
    MainWindow w;
    w.show();

    QTest::keyClicks(&(w.getTextEdit()), "Test");
    w.getQAction().trigger();

    QCOMPARE(w.getTextEdit().toPlainText(), "Test");

    QCOMPARE(w.getTextEdit().alignment(), Qt::AlignRight);

}
