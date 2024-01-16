#ifndef GAME_H
#define GAME_H

#include "actor.h"
#include "tile.h"
#include <vector>
#include <QObject>
#include <QGraphicsScene>

class Game: public QObject{
    Q_OBJECT
    Q_PROPERTY(int mapSize READ mapSize FINAL)
    Q_PROPERTY(std::vector<Tile *> map READ map FINAL)
    Q_PROPERTY(std::vector<Actor *> actors READ actors FINAL)
    Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleHasChanged FINAL)
private:
    /* Members */
    int RES_X, RES_Y;
    int m_mapSize, m_tileSize, player_score;
    std::vector<Tile *> m_map;
    std::vector<Actor *> m_actors;
    bool checkerboard = false;
    QGraphicsScene *scene;
    qreal m_scale;
    void updateScale();
    /* Methods */
    bool eventFilter(QObject *watched, QEvent *event);

public:
    Game(int tilesize, int mapSize, int RES_X, int RES_Y, QGraphicsScene *scene);
    int mapSize();
    qreal scale();
    std::vector<Tile *> map();
    std::vector<Actor *> actors();
    void update_scene();
    void setScale(qreal scale);
};

#endif // GAME_H
