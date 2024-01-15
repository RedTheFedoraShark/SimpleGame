// #include "mainwindow.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene  *scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 600, 800);
    QGraphicsView   *view  = new QGraphicsView();
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(scene);
    view->setFixedSize(800, 600);
    view->show();
    return a.exec();
}
