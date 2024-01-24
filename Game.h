#ifndef GAME_H
#define GAME_H

#include "actor.h"
#include "gametextitem.h"
#include "tile.h"
#include <vector>
#include <QObject>
#include <QGraphicsScene>

class Game: public QObject{
    Q_OBJECT
    Q_PROPERTY(int mapSize READ mapSize FINAL)
    Q_PROPERTY(std::vector<Tile *> map READ map FINAL)
    Q_PROPERTY(std::vector<Actor *> actors READ actors FINAL)
    Q_PROPERTY(qreal scale READ scale WRITE setScale FINAL)
    /* above macro declarations are legacy code, however I wish not to have to deal with deleting them in case something breaks. */
private:
    /* Members */
    int RES_X, RES_Y;  // global resolution values, it's the size default resolution and size of scene, as well as minimum size of the window
    int m_mapSize, m_tileSize, player_score; // size of a single row, size of a side of a single tile and current player score
    std::vector<Tile *> m_map;
    std::vector<Actor *> m_actors;
    bool debug = false;
    bool pause = false;
    QGraphicsScene *scene;
    qreal m_scale;
    gameTextItem *scoreCounter;
    int spawnTimer;
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
    bool checkCollide(int index);
    bool playerWillCollide(int x, int y);
    bool actorWillCollide(int x, int y, int index);
    void toggleMenu();
    void nextTurn();
    void actorAttack(int index);
    int findDir(int vx, int vy, int wx, int wy);
    void addScoreCounter();
    void updateScoreCounter();
    void updateScoreCounterPosition();
    void decide(int index);

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
    int getScore();
    void cleanUp();

signals:
    void gameOver();
};

#endif // GAME_H
