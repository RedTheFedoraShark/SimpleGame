#ifndef GAMETEXTITEM_H
#define GAMETEXTITEM_H

#include "qgraphicsitem.h"
class gameTextItem : public QGraphicsTextItem
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText FINAL)
    QString m_text;
public:
    gameTextItem(QGraphicsItem * parent=0);
    QString text();
    void setText(QString text);
};

#endif // GAMETEXTITEM_H
