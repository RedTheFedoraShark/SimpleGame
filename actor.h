#ifndef ACTOR_H
#define ACTOR_H
#include "actorclass.h"
#include "enums.h"

class Actor: QObject
{
private:
    Q_OBJECT
    Q_PROPERTY(ActorClass profession READ profession WRITE setProfession FINAL)
    Q_PROPERTY(qint16 x READ x WRITE setX NOTIFY xChanged FINAL)
    Q_PROPERTY(qint16 y READ y WRITE setY NOTIFY yChanged FINAL)
    Q_PROPERTY(qint16 AP READ AP WRITE setAP NOTIFY APChanged FINAL)
    Q_PROPERTY(Directions direction READ direction WRITE setDirection NOTIFY directionChanged FINAL)
    ActorClass m_profesion;
    qint16 m_x, m_y, m_AP;
    Directions m_direction;
public:
    Actor();
    void move();
    ActorClass profession();
    qint16 x();
    qint16 y();
    qint16 AP();
    Directions direction();
    void setProfession();
    void setX();
    void setY();
    void setAP();
    void setDireciton();

};

class Player: Actor{};

class Enemy: Actor{};

#endif // ACTOR_H
