#include "mainwindow.h"
#include <QApplication>
#include "unittest.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTest::qExec(new UnitTest(), argc, argv); // Запускаем выполнения теста
    return  0;
}
