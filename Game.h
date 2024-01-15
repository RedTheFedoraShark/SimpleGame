#ifndef GAME_H
#define GAME_H

#include "actor.h"
#include "tile.h"
#include <vector>
#include <QObject>

class Game: public QObject{
    Q_OBJECT
    Q_PROPERTY(int mapSize READ mapSize FINAL)
    Q_PROPERTY(std::vector<Tile *> map READ map FINAL)
    Q_PROPERTY(std::vector<Actor *> actors READ actors FINAL)
private:
    int m_mapSize;
    std::vector<Tile *> m_map;
    std::vector<Actor *> m_actors;
    bool checkerboard = false;

public:
    Game(int mapSize, int RES_X, int RES_Y);
    int mapSize();
    std::vector<Tile *> map();
    std::vector<Actor *> actors();
};

#endif // GAME_H
