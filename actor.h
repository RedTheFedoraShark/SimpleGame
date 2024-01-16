#ifndef ACTOR_H
#define ACTOR_H
#include "enums.h"
#include <QObject>
#include <QGraphicsPixmapItem>

class Actor: public QObject, public QGraphicsPixmapItem
{
private:
    Q_OBJECT
    Q_PROPERTY(int x READ x WRITE setX FINAL)
    Q_PROPERTY(int y READ y WRITE setY FINAL)
    Q_PROPERTY(int AP READ AP WRITE setAP FINAL)
    Q_PROPERTY(int range READ range WRITE setRange FINAL)
    Q_PROPERTY(QString name READ name WRITE setName FINAL)
    Q_PROPERTY(Directions direction READ direction WRITE setDirection FINAL)
    int m_x, m_y, m_AP, m_range;
    Directions m_direction;
    QString m_name;
public:
    Actor();
    void move();
    int x();
    int y();
    int AP();
    int range();
    QString name();
    Directions direction();
    void setX(int x);
    void setY(int y);
    void setAP(int AP);
    void setRange(int range);
    void setName(QString name);
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
