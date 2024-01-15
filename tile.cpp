#include "tile.h"


Tile::Tile(int posx, int posy, bool checker)
{
    if (checker)
        this->setPixmap(QPixmap(":/gfx/whitetile.png"));
    else
        this->setPixmap(QPixmap(":/gfx/blacktile.png"));
    this->setPos(posx, posy);
}
