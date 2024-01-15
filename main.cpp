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
    QApplication a(argc, argv);
    QGraphicsScene  *scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, RES_X, RES_Y);
    QGraphicsView   *view  = new QGraphicsView();
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(scene);
    Game *game = new Game(5, RES_X, RES_Y);
    // scene->addItem(game->map()[1]);
    for (int i = 0; i < (game->mapSize()*game->mapSize()); i++)
    {
        scene->addItem(game->map()[i]);
    }
    for (long long unsigned int i = 0; i < game->actors().size(); i++)
    {
        scene->addItem(game->actors()[i]);
    }
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
