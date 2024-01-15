#ifndef GAME_H
#define GAME_H

#include "actor.h"
#include "tile.h"
#include <vector>

class Game{
private:
    std::vector<Tile> map;
    std::vector<Actor> actors;

public:
    Game();
};

#endif // GAME_H
