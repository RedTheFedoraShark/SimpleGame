#include "actorclass.h"


ActorClass::ActorClass(){}
ActorClass::ActorClass(QString name, int range)
{
    this->setName(name);
    this->setRange(range);
}

void ActorClass::setName(QString name) { this->m_name = name; }
void ActorClass::setRange(int range) { this->m_range = range; }
QString ActorClass::name() { return m_name; }
int ActorClass::range() { return m_range; }
