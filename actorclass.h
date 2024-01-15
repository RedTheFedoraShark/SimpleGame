#ifndef ACTORCLASS_H
#define ACTORCLASS_H
#include <QObject>
#include <QGraphicsPixmapItem>
class ActorClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName FINAL)
    Q_PROPERTY(int range READ range WRITE setRange FINAL)
private:
    QString m_name;
    int m_range;

public:
    ActorClass();
    ActorClass(QString name, int range);
    void setName(QString name);
    void setRange(int range);
    QString name();
    int range();
};

#endif // ACTORCLASS_H
