// #include "mainwindow.h"
#include "Game.h"
#include "tile.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>

int main(int argc, char *argv[])
{
    int RES_X = 800;
    int RES_Y = 600;
    int TILE_SIZE = 100;
    int MAP_SIZE = 7;
    QApplication a(argc, argv);
    QGraphicsScene  *scene = new QGraphicsScene();
    QGraphicsView   *view  = new QGraphicsView();
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(scene);
    Game *game = new Game(TILE_SIZE, MAP_SIZE, RES_X, RES_Y, scene);
    view->setMinimumWidth(RES_X);
    view->setMinimumHeight(RES_Y);
    // view->resize(805, 605);
    // view->setFixedSize(805, 605);
    // view->setMinimumSize();
    view->setSceneRect(0, 0, RES_X - 5,  RES_Y - 5);
    view->setBackgroundBrush(Qt::black);
    view->show();
    return a.exec();
}
