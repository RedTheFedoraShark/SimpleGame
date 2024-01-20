#include "actor.h"
#include "qpainter.h"

Actor::Actor(int points) { this->m_direction = NORTH; this->m_points = points;}
int Actor::x() { return this->m_x; }
int Actor::y() { return this->m_y; }
int Actor::AP() { return this->m_AP; }
int Actor::range() { return this->m_range; }
int Actor::points() { return this->m_points; }
QString Actor::name() { return this->m_name; }
Directions Actor::direction() { return this->m_direction;}
void Actor::setX(int x) { this->m_x = x; }
void Actor::setY(int y) { this->m_y = y; }
void Actor::setAP(int AP){ this->m_AP = AP; }
void Actor::setRange(int range) { this->m_range = range; }
void Actor::setName(QString name) { this->m_name = name; }
void Actor::setDirection(Directions direction) { this->m_direction = direction; }
void Actor::move(int x, int y) { this->m_x += x; this->m_y += y;}
void Actor::turn(int dir)
{
    /* set direction mechanically*/
    int d = (this->direction()+dir) % 8; d = (d<0) ? 8+d : d;
    this->setDirection(Directions(d));
    /* Rotate. Create new transparent Pixmap and using QPainter, rotate it and scale down to 100, 100 again.*/
    QPixmap *map = new QPixmap(this->pixmap().size());
    map->fill(QColor::fromRgb(0, 0, 0, 0)); //the new pixmap must be transparent.
    QPainter* p = new QPainter(map);
    QSize size = this->pixmap().size();
    p->translate(size.height()/2,size.height()/2);
    int angle = this->direction()*45;
    p->rotate(angle);
    p->translate(-size.height()/2,-size.height()/2);
    p->drawPixmap(0, 0, this->originalMap);
    p->end();
    delete p;
    this->setPixmap(*map);
}

Player::Player(int posx, int posy) : Actor(0)
{
    this->setX(posx);
    this->setY(posy);
}

Enemy::Enemy(int posx, int posy, int middle, int points) : Actor(points)
{
    this->setX(posx);
    this->setY(posy);
    this->middle = middle;
    // Wow I didn't know 0/0 is equal to 1. You learn every day.
    int vx = (middle - posx == 0) ? 0 : (middle - posx)/abs(middle - posx);
    int vy = (middle - posy == 0) ? 0 :  (middle - posy)/abs(middle - posy);
    Directions dir;
    /* following conversion of vector of direction to direction enum seems random.
     * It it not. I just spent 10 minutes analysing an A5 page filled with calculations.
     * it's just substracting vector's members from a constant depending on vy */
    if (vy < 0) dir = (9+vx+vy>7) ? Directions((9+vx+vy)-8) : Directions(9+vx+vy);
    else if (vy > 0) dir = (5-vx-vy>7) ? Directions((5-vx-vy)-8) : Directions(5-vx-vy);
    else dir = (4-2*vx>7) ? Directions((4-2*vx)-8) : Directions(4-2*vx);
    this->setDirection(dir);
}


Test_Player::Test_Player(int posx, int posy) : Player(posx, posy)
{
    this->setPixmap(QPixmap(":/gfx/blue_knight.png"));
    this->setRange(1);
    this->originalMap = this->pixmap();
}

Pawn::Pawn(int posx, int posy, int middle) : Enemy(posx, posy, middle, 100)
{
    this->setPixmap(QPixmap(":/gfx/goblin.png"));
    this->setRange(1);
    this->originalMap = this->pixmap();
}

