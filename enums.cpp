#include "enums.h"

std::vector<int> directionVector(Directions dir)
{
    {
        std::vector<int> v(2);
        switch (dir)
        {
        case NORTH:
            v[0] = 0; v[1] = -1;
            break;

        case NORTHEAST:
            v[0] = 1; v[1] = -1;
            break;

        case EAST:
            v[0] = 1; v[1] = 0;
            break;

        case SOUTHEAST:
            v[0] = 1; v[1] = 1;
            break;

        case SOUTH:
            v[0] = 0; v[1] = 1;
            break;

        case SOUTHWEST:
            v[0] = -1; v[1] = -1;
            break;

        case WEST:
            v[0] = -1; v[1] = 0;
            break;

        case NORTHWEST:
            v[0] = -1; v[1] = -1;
            break;

        default:
            break;
        }
        return {v[0], v[1]};
    }
}
