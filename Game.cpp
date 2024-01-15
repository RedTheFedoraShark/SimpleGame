#include "Game.h"
#include "tile.h"
#include "actor.h"
// #include <QDebug>
Game::Game(int mapSize, int RES_X, int RES_Y)
{
    // init map
    this->m_mapSize = mapSize;
    int x=(RES_X-(mapSize*100))/2, y=(RES_Y-(mapSize*100))/2;
    for (int i = 0; i < mapSize*mapSize; i++)
    {
        if (x == ((RES_X-(mapSize*100))/2) + (mapSize*100))
        {
            x = (RES_X-(mapSize*100))/2;
            y += 100;
        }
        // qDebug() << x << ";" << y <<"\n";
        this->m_map.push_back(new Tile(x,y, this->checkerboard));
        this->checkerboard = (checkerboard) ? false : true ;
        x+=100;
    }
    // init player
    this->m_actors.push_back(new Test_Player(mapSize/2,mapSize/2));
    x = ((RES_X-(mapSize*100))/2) + (mapSize/2) *100;
    y = ((RES_Y-(mapSize*100))/2) + (mapSize/2) *100;
    this->m_actors[0]->setPos(x, y);
}

int Game::mapSize() { return this->m_mapSize; }
std::vector<Tile *> Game::map() { return this->m_map; }

std::vector<Actor *> Game::actors() { return this->m_actors; }
