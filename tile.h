#ifndef TILE_H
#define TILE_H
#include <QObject>
#include <QGraphicsPixmapItem>

class Tile: public QGraphicsPixmapItem
{
private:
    bool full;
public:
    Tile(int posx, int posy, bool checker);
};

#endif // TILE_H
