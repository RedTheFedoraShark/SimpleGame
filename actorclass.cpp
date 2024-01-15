#include "actorclass.h"

ActorClass::ActorClass(QString name, int range)
{
    this->setName(name);
    this->setRange(range);
}

void ActorClass::setName(QString name) { m_name = name; }

void ActorClass::setRange(qint16 range) { m_range = range; }

QString ActorClass::name() { return m_name; }
qint16 ActorClass::range() { return m_range; }
