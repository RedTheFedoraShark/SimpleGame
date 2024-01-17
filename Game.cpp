#include "Game.h"
#include "qcoreevent.h"
#include <QKeyEvent>
#include "tile.h"
#include "actor.h"
#include <QDebug>
#include <random>
Game::Game(int tileSize, int mapSize, int RES_X, int RES_Y, QGraphicsScene *scene)
{
    // init globals
    this->RES_X = RES_X; this->RES_Y = RES_Y;
    this->m_scale = 1.0;
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
        this->scene->addItem(this->m_map[i]);
        this->checkerboard = (checkerboard) ? false : true ;
        x+=tileSize*scale();
    }

    // init player
    this->addActor(new Test_Player(mapSize/2, mapSize/2));
    // init first enemy
    this->spawnRandom();
}

void Game::updateScale()
/* update all tiles' and actors' scale */
{
    // qDebug()<<"I was called";
    int x=round((RES_X-(m_mapSize*m_tileSize*m_scale))/2);
    int y=round((RES_Y-(m_mapSize*m_tileSize*m_scale))/2);
    // qDebug()<<x<<" "<<RES_X<<" "<<m_mapSize<<m_tileSize<<" "<<m_scale<<" "<<(m_mapSize*m_tileSize*m_scale);
    for (int i = 0; i < m_mapSize*m_mapSize; i++)
    {
        if (x == round((RES_X-(m_mapSize*m_tileSize*m_scale))/2) + round((m_mapSize*m_tileSize*scale())))
        {
            x=round((RES_X-(m_mapSize*m_tileSize*m_scale))/2);
            y += round(m_tileSize*scale());
        }
        // qDebug() << x << ";" << y <<"\n";
        this->m_map[i]->setScale(scale());
        this->m_map[i]->setPos(x, y);
        x+=m_tileSize*scale();
    }
    for (long unsigned int i = 0; i < actors().size(); i++)
    {
        this->m_actors[i]->setScale(scale());
        // qreal scalingCorrection = (scale()-1)/2;
        this->m_actors[i]->setTransformOriginPoint(QPoint(0, 0));
        x = (RES_X-m_mapSize*m_tileSize*scale())/2 + (m_actors[i]->x())*m_tileSize*scale();
        y = (RES_Y-m_mapSize*m_tileSize*scale())/2 + (m_actors[i]->y())*m_tileSize*scale();
        this->m_actors[i]->setPos(x, y);
    }
}

void Game::setScale(qreal scale) { if(scale >= 0.4 && scale < 1.6)this->m_scale = scale; this->updateScale(); }

void Game::addActor(Actor *actor)
/* spawn a specified actor */
{
    int i = this->m_actors.size();
    this->m_actors.push_back(actor);
    this->scene->addItem(actor);
    this->m_actors[i]->setTransformOriginPoint(QPoint(0, 0));
    this->m_actors[i]->setScale(this->m_scale);
    int x = (RES_X-m_mapSize*m_tileSize*scale())/2 + m_actors[i]->x()*m_tileSize*scale();
    int y = (RES_Y-m_mapSize*m_tileSize*scale())/2 + m_actors[i]->y()*m_tileSize*scale();
    this->m_actors[i]->setPos(x, y);
}

void Game::spawnRandom()
/* spawn a Pawn enemy on random unoccupied tile*/
{
    int ex, ey;
    bool loop = true;
    while (loop) // make sure enemy won't be generated on top of the player
    {
        ey = this->randomUniform(0, m_mapSize-1);
        ex = this->randomUniform(0, m_mapSize-1);
        for(int i = 0; i < m_actors.size(); i++)
        {
            if (m_actors[i]->x() == ex && m_actors[i]->y() == ey)
            {
                loop = true;
                break;
            }
            else
            {
                loop = false;
            }
        }
    }
    this->addActor(new Pawn(ex, ey, m_mapSize/2));
}

void Game::rotActor(int dir, int index)
/* turn actor[index] by 1 step (45 degrees) in dir direction */
{
    // qreal scalingCorrection = (scale()-1)/2;
    // qDebug()<<this->m_actors[index]->pixmap().size();
    // qDebug()<<this->m_actors[index]->scale();
    // int x = (RES_X-m_mapSize*m_tileSize*1)/2 + (m_actors[index]->x()+0.5)*m_tileSize*1 - this->m_actors[index]->pos().x();
    // int y = (RES_Y-m_mapSize*m_tileSize*1)/2 + (m_actors[index]->y()+0.5)*m_tileSize*1 - this->m_actors[index]->pos().y();
    // qDebug()<<this->m_actors[index]->pos()<<x<<y;
    // this->m_actors[index]->setTransformOriginPoint(QPoint(50, 50));
    // qDebug()<<this->m_actors[index]->transformOriginPoint();
    this->m_actors[index]->turn(dir);
}

void Game::delActor(int index)
/* delete actor on index and remove it from scene */
{
    // this->scene->removeItem(this->m_);
    qDebug()<<this->m_actors.size();
    this->scene->removeItem(this->m_actors[index]);
    this->m_actors.erase(this->m_actors.begin()+index);
    qDebug()<<this->m_actors.size();
}

bool Game::movActor(int index, Directions dir = NULL)
/* attempt to move actor on index in dir direction. By default move it forwards */
{
    if (dir == NULL) dir = m_actors[index]->direction();
    int px = m_actors[index]->x();
    int py = m_actors[index]->y();
//     for (int i = 0; i < m_actors.size(); i++)
//     {

//     }
}

bool Game::movPlayer(Directions dir)
/* this actually doesn't move the player, as it would be more trouble than it's worth. Instead it's moving everything towards the player. */
{
    int x, y;
    // whether to add(true) or remove(false) or leave alone (null) r(ow) or c(olumn) at beg(inning) or end of the square board
    bool rbeg = NULL, rend = NULL, cbeg = NULL, cend = NULL;
    switch (dir)
    {
    case NORTH:
        x = 0; y = 1;
        rbeg = true; rend = false;
        break;

    case NORTHEAST:
        x = -1; y = 1;
        rbeg = true; rend = false; cbeg = false; cend = true;
        break;

    case EAST:
        x = -1; y = 0;
        cbeg = false; cend = true;
        break;

    case SOUTHEAST:
        x = -1; y = -1;
        rbeg = false; rend = true; cbeg = false; cend = true;
        break;

    case SOUTH:
        x = 0; y = -1;
        rbeg = false; rend = true;
        break;

    case SOUTHWEST:
        x = 1; y = 1;
        rbeg = false; rend = true; cbeg = true; cend = false;
        break;

    case WEST:
        x = 1; y = 0;
        cbeg = true; cend = false;
        break;

    case NORTHWEST:
        x = 1; y = 1;
        rbeg = true; rend = false; cbeg = true; cend = false;
        break;

    default:
        return false;
    }
    for (int i = 1; i < m_actors.size(); i++) // move everyone down
    {
        m_actors[i]->move(x, y);
        if(m_actors[i]->x() >= m_mapSize || m_actors[i]->x() < 0 || m_actors[i]->y() >= m_mapSize || m_actors[i]->y() < 0)
        { this->delActor(i); continue; }
        m_actors[i]->moveBy(x*m_tileSize*m_scale, y*m_tileSize*m_scale);
    }
    for (int i = 0; i < m_map.size(); i++)
    {
        i f (cend){}
    }
    return true;
}

void Game::addTile(int x, int y)
{
    int i = this->m_map.size();
    this->m_map.push_back(new Tile(x,y, this->checkerboard));
    this->m_map[i]->setScale(this->m_scale);
    this->scene->addItem(this->m_map[i]);
}

int Game::randomUniform(int min, int max)
/* return single integer selected randomly from <min, max> distributed uniformly */
{
    std::random_device device;
    std::mt19937 engine(device());
    std::uniform_int_distribution uni_distribution(min, max);
    return uni_distribution(engine);
}


int Game::mapSize() { return this->m_mapSize; }
qreal Game::scale() { return this->m_scale; }
std::vector<Tile *> Game::map() { return this->m_map; }

std::vector<Actor *> Game::actors() { return this->m_actors; }

bool Game::eventFilter(QObject *object, QEvent *event)
/* handle event recieved from view, used for detecting user input */
{
    if (event->type()==QEvent::KeyPress) {
        QKeyEvent* key = (QKeyEvent*)event;
        switch(key->key())
        {
        case Qt::Key_Plus:
            this->setScale(this->scale()+0.1);
            return true;

        case Qt::Key_Minus:
            this->setScale(this->scale()-0.1);
            return true;

        case Qt::Key_W:
            return true;

        case Qt::Key_A:
            return true;

        case Qt::Key_S:
            return true;

        case Qt::Key_D:
            return true;

        case Qt::Key_E:
            this->rotActor(+1, 0);
            return true;

        case Qt::Key_Q:
            this->rotActor(-1, 0);
            return true;

        case Qt::Key_F12: // turn on debug mode
            this->debug = (this->debug) ? false : true;
            return true;

        case Qt::Key_F11: // despawn an actor
            if (this->debug && m_actors.size() > 1)
            {
                this->delActor(this->m_actors.size()-1);
                return true;
            }
            return QObject::eventFilter(object, event);

        case Qt::Key_F10: // spawn an enemy Pawn
            if (this->debug && m_actors.size() < m_mapSize*m_mapSize)
            {
                this->spawnRandom();
                return true;
            }
            return QObject::eventFilter(object, event);

        default:
            return QObject::eventFilter(object, event);
        }
    } else {
        return QObject::eventFilter(object, event);
    }
    return false;
}
