#include "actor.h"

Actor::Actor() { this->m_direction = NORTH; }
int Actor::x() { return this->m_x; }
int Actor::y() { return this->m_y; }
int Actor::AP() { return this->m_AP; }
int Actor::range() { return this->m_range; }
QString Actor::name() { return this->m_name; }
Directions Actor::direction() { return this->m_direction;}
void Actor::setX(int x) { this->m_x = x; }
void Actor::setY(int y) { this->m_y = y; }
void Actor::setAP(int AP){ this->m_AP = AP; }
void Actor::setRange(int range) { this->m_range = range; }
void Actor::setName(QString name) { this->m_name = name; }
void Actor::setDirection(Directions direction) { this->m_direction = direction; }

Player::Player(int posx, int posy)
{
    this->setX(posx);
    this->setY(posy);
}

Test_Player::Test_Player(int posx, int posy) : Player(posx, posy)
{
    this->setPixmap(QPixmap(":/gfx/blueactor.png"));
}
