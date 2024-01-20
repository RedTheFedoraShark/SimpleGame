#include "tile.h"


Tile::Tile(int posx, int posy, int num)
{
    QString path = ":/gfx/grass";
    QString n = QString::number(num);
    QString ext = ".png";
    this->setPixmap(QPixmap(QString(path+n+ext)));
    this->setPos(posx, posy);
}
