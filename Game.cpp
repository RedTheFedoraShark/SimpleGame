#include "Game.h"
#include "qcoreevent.h"
#include <QKeyEvent>
#include "tile.h"
#include "actor.h"
#include <QDebug>
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
        this->checkerboard = (checkerboard) ? false : true ;
        x+=tileSize*scale();
    }
    // init player
    this->addActor(new Test_Player(mapSize/2, mapSize/2));
    x = (RES_X-(mapSize*tileSize*scale()))/2 + (this->actors()[0]->x())*tileSize*scale();
    y = (RES_Y-(mapSize*tileSize*scale()))/2 + (this->actors()[0]->y())*tileSize*scale();
    // qDebug() << x << y;
    this->m_actors[0]->setPos(x, y);
    this->m_actors[0]->setScale(scale());
    this->update_scene();
    // set transform point for rotation
    // this->m_actors[0]->setTransformOriginPoint(QPoint(m_tileSize*scale()/2, m_tileSize*scale()/2));
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

bool Game::eventFilter(QObject *object, QEvent *event)
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

        default:
            return QObject::eventFilter(object, event);
        }
    } else {
        return QObject::eventFilter(object, event);
    }
    return false;
}

void Game::setScale(qreal scale) { if(scale >= 0.4 && scale < 1.6)this->m_scale = scale; this->updateScale(); }

void Game::addActor(Actor *actor)
{
    int i = this->m_actors.size();
    this->m_actors.push_back(actor);
    this->m_actors[i]->setTransformOriginPoint(QPoint(0, 0));
    int x = (RES_X-m_mapSize*m_tileSize*scale())/2 + m_actors[i]->x()*m_tileSize*scale();
    int y = (RES_Y-m_mapSize*m_tileSize*scale())/2 + m_actors[i]->y()*m_tileSize*scale();
    this->m_actors[i]->setPos(x, y);
}

void Game::rotActor(int dir, int index)
{
    // qreal scalingCorrection = (scale()-1)/2;
    // qDebug()<<this->m_actors[index]->pixmap().size();
    // qDebug()<<this->m_actors[index]->scale();
    // int x = (RES_X-m_mapSize*m_tileSize*1)/2 + (m_actors[index]->x()+0.5)*m_tileSize*1 - this->m_actors[index]->pos().x();
    // int y = (RES_Y-m_mapSize*m_tileSize*1)/2 + (m_actors[index]->y()+0.5)*m_tileSize*1 - this->m_actors[index]->pos().y();
    // qDebug()<<this->m_actors[index]->pos()<<x<<y;
    // this->m_actors[index]->setTransformOriginPoint(QPoint(50, 50));
    // qDebug()<<this->m_actors[index]->transformOriginPoint();
    // this->m_actors[index]->turn(dir);
}

int Game::mapSize() { return this->m_mapSize; }
qreal Game::scale() { return this->m_scale; }
std::vector<Tile *> Game::map() { return this->m_map; }

std::vector<Actor *> Game::actors() { return this->m_actors; }
