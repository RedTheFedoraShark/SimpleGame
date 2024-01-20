#ifndef WINDOW_H
#define WINDOW_H

#include "Game.h"
#include "qgraphicsscene.h"
#include "qgraphicsview.h"
class window : public QObject
{
    Q_OBJECT

    int RES_X = 800;
    int RES_Y = 600;
    int TILE_SIZE = 100;
    int MAP_SIZE = 7;
    QGraphicsScene *scene;
    QGraphicsView  *view;
    Game *game;
    gameTextItem *gameOverMessage;
    /*methods*/
    void playAgain();
    void addGameOverMessage();
    void updateGameOverMessage();
    void deleteGameOverMessage();
    void updateGameOverMessagePos();
protected:
    bool eventFilter(QObject *object, QEvent *event) override;
public:
    window();
public slots:
    void gameOver();
};

#endif // WINDOW_H
