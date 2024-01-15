#ifndef ACTOR_H
#define ACTOR_H
#include "actorclass.h"
#include "enums.h"
#include <QObject>
#include <QGraphicsPixmapItem>

class Actor: public QObject, public QGraphicsPixmapItem
{
private:
    Q_OBJECT
    Q_PROPERTY(ActorClass *profession READ profession WRITE setProfession FINAL)
    Q_PROPERTY(int x READ x WRITE setX FINAL)
    Q_PROPERTY(int y READ y WRITE setY FINAL)
    Q_PROPERTY(int AP READ AP WRITE setAP FINAL)
    Q_PROPERTY(Directions direction READ direction WRITE setDirection FINAL)
    ActorClass *m_profession;
    int m_x, m_y, m_AP;
    Directions m_direction;
public:
    Actor();
    void move();
    ActorClass *profession();
    int x();
    int y();
    int AP();
    Directions direction();
    void setProfession(ActorClass *profession);
    void setX(int x);
    void setY(int y);
    void setAP(int AP);
    void setDirection(Directions direction);

};

class Player: public Actor
{
public:
    Player(int posx, int posy);
};

class Test_Player: public Player
{
public:
    Test_Player(int posx, int posy);
};

// class Enemy: Actor{};

#endif // ACTOR_H
