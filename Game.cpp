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
        this->addTile(x, y);
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
    int x=round((RES_X-(m_mapSize*m_tileSize*m_scale))/2);
    int y=round((RES_Y-(m_mapSize*m_tileSize*m_scale))/2);
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
        this->m_map[i]->setZValue(0);
        x+=m_tileSize*scale();
    }
    for (long unsigned int i = 0; i < actors().size(); i++)
    {
        this->m_actors[i]->setScale(scale());
        // this->m_actors[i]->setTransformOriginPoint(QPoint(0, 0));
        x = (RES_X-m_mapSize*m_tileSize*scale())/2 + (m_actors[i]->x())*m_tileSize*scale();
        y = (RES_Y-m_mapSize*m_tileSize*scale())/2 + (m_actors[i]->y())*m_tileSize*scale();
        this->m_actors[i]->setPos(x, y);
        this->m_actors[i]->setZValue(1);
    }
}


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
        for(long unsigned int i = 0; i < m_actors.size(); i++)
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

bool Game::checkCollide(int index)
{
    for(long unsigned int i = 0; i < m_actors.size(); i++)
    {
        if (i == (long unsigned)index)
            continue;
        if (m_actors[index]->collidesWithItem(m_actors[i]))
        {
            return false;
        }
    }
    return true;
}

void Game::rotActor(int dir, int index)
/* turn actor[index] by 1 step (45 degrees) in dir direction */
{
    this->m_actors[index]->turn(dir);
}

void Game::delActor(int index)
/* delete actor on index and remove it from scene */
{
    this->scene->removeItem(this->m_actors[index]);
    this->m_actors.erase(this->m_actors.begin()+index);
}

void Game::addTile(int x, int y)
{
    int i = this->m_map.size();
    this->m_map.push_back(new Tile(x,y, this->checkerboard));
    this->checkerboard = (this->checkerboard) ? false : true;
    this->m_map[i]->setScale(this->m_scale);
    this->scene->addItem(this->m_map[i]);
}

void Game::addTile(int x, int y, int index)
{
    if (index >= this->m_map.size())
    {
        this->addTile(x, y);
    }
    else
    {
        this->m_map.insert(m_map.begin()+index, new Tile(x,y, this->checkerboard));
        this->checkerboard = (this->checkerboard) ? false : true;
        this->m_map[index]->setScale(this->m_scale);
        this->scene->addItem(this->m_map[index]);
    }
}

void Game::delTile(int index)
{
    this->scene->removeItem(this->m_map[index]);
    this->m_map.erase(m_map.begin()+index);
}

void Game::delTile(int begin, int end)
{
    for(int i = begin; i < end; i++)
    {
        this->scene->removeItem(this->m_map[i]);
    }
    this->m_map.erase(m_map.begin()+begin, m_map.begin()+end);
}

bool Game::playerWillCollide(int x, int y)
{
    for(int i = 1; i < m_actors.size(); i++)
    {
        qDebug()<<"Checking player "<<i;
        qDebug()<<m_actors[0]->x()<< m_actors[0]->y();
        qDebug()<<m_actors[i]->x()<< m_actors[i]->y();
    if (m_actors[0]->x()+x == m_actors[i]->x() &&
        m_actors[0]->y()+y == m_actors[i]->y() ) return true;
    }
    return false;
}

bool Game::movActor(Directions dir, int index)
/* attempt to move actor on index in dir direction. By default move it forwards */
{
    int x, y; // init relative x and y by which actor shall be moved
    // convert Directions to x and y modifiers
    switch (dir)
    {
    case NORTH:
        x = 0; y = -1;
        break;

    case NORTHEAST:
        x = 1; y = -1;
        break;

    case EAST:
        x = 1; y = 0;
        break;

    case SOUTHEAST:
        x = 1; y = 1;
        break;

    case SOUTH:
        x = 0; y = 1;
        break;

    case SOUTHWEST:
        x = -1; y = -1;
        break;

    case WEST:
        x = -1; y = 0;
        break;

    case NORTHWEST:
        x = -1; y = -1;
        break;

    default:
        return false;
    }
    // move actor, check if it collided and if true, move it back
    m_actors[index]->moveBy(x*m_tileSize*m_scale, y*m_tileSize*m_scale);
    if (!checkCollide(index))
    { m_actors[index]->moveBy((-x)*m_tileSize*m_scale, (-y)*m_tileSize*m_scale); return false; }
    m_actors[index]->move(x, y);
    return true;
}

bool Game::movPlayer(Directions dir)
/* this actually doesn't move the player, as it would be more trouble than it's worth.
 * Instead it's moving everything else in the other direction. (yes, that's easier.) */
{
    int dx, dy, x=0, y=0; // dx, dx - relative x and y by which actors will be moved ; negative value of players movement direction
                          // x and y are dummies for tile manip to work
    // whether to add(true) or remove(false) or leave alone (null) r(ow) or c(olumn) at beg(inning) or end of the square board
    // convert Directions to x and y modifiers
    switch (dir)
    {
    case NORTH:
        dx = 0; dy = 1;
        if(this->playerWillCollide(-dx, -dy)) return false;
        this->delTile(m_map.size()-m_mapSize, m_map.size()); //remove last row
        for(int i = 0; i < m_mapSize; i++) // insert a row of new tiles at the beginning
        {
            this->addTile(x, y, i);
        }
        break;

    case NORTHEAST:
        dx = -1; dy = 1;
        if(this->playerWillCollide(-dx, -dy)) return false;
        this->delTile(m_map.size()-m_mapSize, m_map.size());
        // m_map.erase(m_map.end()-m_mapSize, m_map.end()); // remove last row
        for (long unsigned int i = 0; i < m_map.size(); i+=m_mapSize) // for each row remove first tile and add one at the end
        {
            this->delTile(i);
            this->addTile(x, y, i+m_mapSize);
        }
        for(int i = 0; i < m_mapSize; i++) // insert a row of new tiles at the beginning
        {
            this->addTile(x, y, 0);
        }
        break;

    case EAST:
        dx = -1; dy = 0;
        if(this->playerWillCollide(-dx, -dy)) return false;
        for (long unsigned int i = 0; i < m_map.size(); i+=m_mapSize) // for each for remove first and add last
        {
            this->delTile(i);
            this->addTile(x, y, i+m_mapSize);
        }
        break;

    case SOUTHEAST:
        dx = -1; dy = -1;
        if(this->playerWillCollide(-dx, -dy)) return false;
        qDebug()<<"Removing first row";
        this->delTile(0, m_mapSize);
        for (long unsigned int i = 0; i < m_map.size(); i+=m_mapSize) // for each for remove first and add last
        {
            qDebug() << "removing "<<i;
            this->delTile(i);
            this->addTile(x, y, i+m_mapSize);
        }
        for(int i = m_map.size(); i < m_mapSize*m_mapSize; i++) // insert a new row at the end
        {
            this->addTile(x, y);
        }
        break;

    case SOUTH:
        dx = 0; dy = -1;
        if(this->playerWillCollide(-dx, -dy)) return false;
        // m_map.erase(m_map.begin(), m_map.end()); // remove first row
        this->delTile(0, m_mapSize);
        for(int i = m_map.size(); i < m_mapSize*m_mapSize; i++) // insert a new row at the end
        {
            this->addTile(x, y);
        }
        break;

    case SOUTHWEST:
        dx = 1; dy = 1;
        if(this->playerWillCollide(-dx, -dy)) return false;
        this->delTile(0, m_mapSize);
        for (long unsigned int i = 0; i < m_mapSize*m_mapSize; i+=m_mapSize) // for each for remove last and add first
        {
            this->delTile(i+m_mapSize-1);
            this->addTile(x, y, i);
        }
        for(int i = m_map.size(); i < m_mapSize*m_mapSize; i++) // insert a new row at the end
        {
            this->addTile(x, y);
        }
        break;

    case WEST:
        dx = 1; dy = 0;
        if(this->playerWillCollide(-dx, -dy)) return false;
        for (long unsigned int i = 0; i < m_mapSize*m_mapSize; i+=m_mapSize) // for each for remove last and add first
        {
            this->delTile(i+m_mapSize-1);
            this->addTile(x, y, i);
        }
        break;

    case NORTHWEST:
        dx = 1; dy = 1;
        if(this->playerWillCollide(-dx, -dy)) return false;
        this->delTile(m_map.size()-m_mapSize, m_map.size()); //remove last row
        for (long unsigned int i = 0; i < m_mapSize*m_mapSize; i+=m_mapSize) // for each for remove last and add first
        {
            this->delTile(i+m_mapSize-1);
            this->addTile(x, y, i);
        }
        for(int i = 0; i < m_mapSize; i++) // insert a row of new tiles at the beginning
        {
            this->addTile(x, y, i);
        }
        break;

    default:
        return false;
    }
    for (long unsigned int i = 1; i < m_actors.size(); i++) // move everyone down
    {
        m_actors[i]->move(dx, dy);
        if(m_actors[i]->x() >= m_mapSize || m_actors[i]->x() < 0 || m_actors[i]->y() >= m_mapSize || m_actors[i]->y() < 0)
        { this->delActor(i); continue; }
        // m_actors[i]->moveBy(x*m_tileSize*m_scale, y*m_tileSize*m_scale);
    }
    this->updateScale();
    return true;
}

void Game::setScale(qreal scale) { if(scale >= 0.4 && scale < 1.6)this->m_scale = scale; this->updateScale(); }

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
        bool numpad = key->modifiers() & Qt::KeyboardModifier::KeypadModifier;
        switch(key->key())
        {
        case Qt::Key_Plus:
            this->setScale(this->scale()+0.1);
            return true;

        case Qt::Key_Minus:
            this->setScale(this->scale()-0.1);
            return true;

        case Qt::Key_8:
            if (!numpad) break;
        case Qt::UpArrow:
        case Qt::Key_W:
            if (this->movPlayer(NORTH))
                return true;
            else
                return QObject::eventFilter(object, event);

        case Qt::Key_9:
        case Qt::Key_PageUp:
        case Qt::Key_E:
            if (this->movPlayer(NORTHEAST))
                return true;
            else
                return QObject::eventFilter(object, event);

        case Qt::Key_6:
            if(!numpad) break;
        case Qt::RightArrow:
        case Qt::Key_D:
            if (this->movPlayer(EAST))
                return true;
            else
                return QObject::eventFilter(object, event);

        case Qt::Key_3:
            if(!numpad) break;
        case Qt::Key_PageDown:
        case Qt::Key_C:
            if (this->movPlayer(SOUTHEAST))
                return true;
            else
                return QObject::eventFilter(object, event);

        case Qt::Key_2:
            if(!numpad) break;
        case Qt::DownArrow:
        case Qt::Key_X:
            if (this->movPlayer(SOUTH))
                return true;
            else
                return QObject::eventFilter(object, event);

        case Qt::Key_1:
            if(!numpad) break;
        case Qt::Key_End:
        case Qt::Key_Z:
            if (this->movPlayer(SOUTHWEST))
                return true;
            else
                return QObject::eventFilter(object, event);

        case Qt::Key_4:
            if(!numpad) break;
        case Qt::LeftArrow:
        case Qt::Key_A:
            if (this->movPlayer(WEST))
                return true;
            else
                return QObject::eventFilter(object, event);

        case Qt::Key_7:
            if(!numpad) break;
        case Qt::Key_Home:
        case Qt::Key_Q:
            if (this->movPlayer(SOUTH))
                return true;
            else
                return QObject::eventFilter(object, event);

        case Qt::Key_Comma:
        case Qt::Key_T:
            this->rotActor(+1, 0);
            return true;

        case Qt::Key_0:
            if(!numpad) break;
        case Qt::Key_R:
            this->rotActor(-1, 0);
            return true;

        case Qt::Key_Escape:
            this->pause = (this->pause)? false : true;
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
    return QObject::eventFilter(object, event);
}
