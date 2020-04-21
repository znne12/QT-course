#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QGraphicsView(parent)
{    
    srand(clock());
    Scene *scence = new Scene(this);
    scence->setSceneRect(rect());
    setScene(scence);
    setFixedSize(800, 600);
    connect(scence, &Scene::scaleUp, this, &MainWindow::setScaleUp);
    connect(scence, &Scene::scaleDown, this, &MainWindow::setScaleDown);
}
MainWindow::~MainWindow()
{

}

void MainWindow::setScaleUp()
{
    scale(1.1, 1.1);
}

void MainWindow::setScaleDown()
{
    scale(0.9, 0.9);
}


