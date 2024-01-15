#ifndef ACTORCLASS_H
#define ACTORCLASS_H
#include <QObject>

class ActorClass : QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName FINAL)
    Q_PROPERTY(qint16 range READ range WRITE setRange FINAL)
private:
    QString m_name;
    qint16 m_range;
public:

    ActorClass(QString name, int range);
    void setName(QString name);
    void setRange(qint16 range);
    QString name();;
    qint16 range();
};

#endif // ACTORCLASS_H
