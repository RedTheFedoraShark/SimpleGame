#include "Game.h"
#include "tile.h"
#include "actor.h"
#include <QDebug>
Game::Game(int tileSize, int mapSize, int RES_X, int RES_Y, QGraphicsScene *scene)
{
    // init globals
    this->RES_X = RES_X; this->RES_Y = RES_Y;
    this->m_scale = 0.8;
    this->scene = scene;
    this->m_mapSize = mapSize;
    this->m_tileSize = tileSize;
    int x=(RES_X-(mapSize*tileSize*scale()))/2, y=(RES_Y-(mapSize*tileSize*scale()))/2;
    for (int i = 0; i < mapSize*mapSize; i++)
    {
        if (x == ((RES_X-(mapSize*tileSize*scale()))/2) + (mapSize*tileSize*scale()))
        {
            x = (RES_X-(mapSize*tileSize*scale()))/2;
            y += tileSize*scale();
        }
        // qDebug() << x << ";" << y <<"\n";
        this->m_map.push_back(new Tile(x,y, this->checkerboard));
        this->m_map[i]->setScale(this->m_scale);
        this->checkerboard = (checkerboard) ? false : true ;
        x+=tileSize*scale();
    }
    // init player
    this->m_actors.push_back(new Test_Player(mapSize/2,mapSize/2));
    x = (RES_X-(mapSize*tileSize*scale()))/2 + (this->actors()[0]->x())*tileSize*scale();
    y = (RES_Y-(mapSize*tileSize*scale()))/2 + (this->actors()[0]->y())*tileSize*scale();
    qDebug() << x << y;
    this->m_actors[0]->setPos(x, y);
    this->m_actors[0]->setScale(scale());

    this->update_scene();
}

void Game::update_scene()
{
    // scene->addItem(game->map()[1]);
    for (int i = 0; i < (this->mapSize()*this->mapSize()); i++)
    {
        this->scene->addItem(this->map()[i]);
    }
    for (long long unsigned int i = 0; i < this->actors().size(); i++)
    {
        this->scene->addItem(this->actors()[i]);
    }
}

void Game::updateScale()
{
    int x=(RES_X-(m_mapSize*m_tileSize*scale()))/2, y=(RES_Y-(m_mapSize*m_tileSize*scale()))/2;
    for (int i = 0; i < m_mapSize*m_mapSize; i++)
    {
        if (x == ((RES_X-(m_mapSize*m_tileSize*scale()))/2) + (m_mapSize*m_tileSize*scale()))
        {
            x = (RES_X-(m_mapSize*m_tileSize*scale())/2);
            y += m_tileSize*scale();
        }
        // qDebug() << x << ";" << y <<"\n";
        this->m_map[i]->setScale(scale());
        this->m_map[i]->setPos(x, y);
        x+=m_tileSize*scale();
    }
    for (long unsigned int i = 0; i < actors().size(); i++)
    {
        this->m_actors[i]->setScale(scale());
        x = (RES_X-(m_mapSize*m_tileSize*scale()))/2 + (m_actors[i]->x())*m_tileSize*scale();
        y = (RES_Y-(m_mapSize*m_tileSize*scale()))/2 + (m_actors[i]->y())*m_tileSize*scale();
        this->m_actors[i]->setPos(x, y);
    }
}

bool Game::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *key = (QKeyEvent*)event;
        int _key = key->key();
        switch (_key)
        {
        case Qt::Key_Plus:
            this->setScale(scale()+0.1);
            return true;

        case Qt::Key_Minus:
            this->setScale(scale()-0.1);
            return true;

        default:
            return false;
        }
    }
    return false;
}

void Game::setScale(qreal scale) { this->m_scale = scale; }
int Game::mapSize() { return this->m_mapSize; }
qreal Game::scale() { return this->m_scale; }
std::vector<Tile *> Game::map() { return this->m_map; }

std::vector<Actor *> Game::actors() { return this->m_actors; }
