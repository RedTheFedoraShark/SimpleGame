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
    Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleChanged FINAL)
private:
    /* Members */
    int RES_X, RES_Y;
    int m_mapSize, m_tileSize, player_score;
    std::vector<Tile *> m_map;
    std::vector<Actor *> m_actors;
    bool checkerboard = false;
    bool debug = false;
    bool pause = false;
    QGraphicsScene *scene;
    qreal m_scale;

    /* Methods */
    int randomUniform(int min, int max);
    void updateScale();
    void addActor(Actor *actor);
    void delActor(int index);
    void rotActor(int dir, int index);
    bool movActor(Directions dir, int index);
    void addTile(int x, int y);
    void addTile(int x, int y, int index);
    void delTile(int index);
    void delTile(int begin, int end);
    bool movPlayer(Directions dir);
    void spawnRandom();
    void pathFind();
    void decide();
    bool checkCollide(int index);
    bool playerWillCollide(int x, int y);
    void toggleMenu();

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

public:
    Game(int tilesize, int mapSize, int RES_X, int RES_Y, QGraphicsScene *scene);
    int mapSize();
    qreal scale();
    std::vector<Tile *> map();
    std::vector<Actor *> actors();
    // void update_scene();
    void setScale(qreal scale);
signals:
    void scaleChanged();
};

#endif // GAME_H
