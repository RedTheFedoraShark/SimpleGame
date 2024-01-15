#include "actor.h"

Actor::Actor() { this->m_profession = new ActorClass("", 1); this->m_direction = NORTH; }
int Actor::x() { return this->m_x; }
int Actor::y() { return this->m_y; }
int Actor::AP() { return this->m_AP; }
ActorClass* Actor::profession() { return this->m_profession;}
Directions Actor::direction() { return this->m_direction;}
void Actor::setProfession(ActorClass *profession){ delete this->m_profession; this->m_profession = profession; }
void Actor::setX(int x) { this->m_x = x; }
void Actor::setY(int y) { this->m_y = y; }
void Actor::setAP(int AP){ this->m_AP = AP; }
void Actor::setDirection(Directions direction) { this->m_direction = direction; }

Player::Player(int posx, int posy)
{
    this->setX(posx);
    this->setY(posy);
}

Test_Player::Test_Player(int posx, int posy) : Player(posx, posy)
{
    this->setPixmap(QPixmap(":/gfx/blueactor.png"));
    this->setProfession(new ActorClass("TestPlayer", 1));
}
