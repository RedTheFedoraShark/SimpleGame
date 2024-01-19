#pragma once
#ifndef ENUMS_H
#define ENUMS_H

#include <vector>

enum Directions {
    NORTH = 0,
    NORTHEAST,
    EAST,
    SOUTHEAST,
    SOUTH,
    SOUTHWEST,
    WEST,
    NORTHWEST
};

std::vector<int> directionVector(Directions dir);

#endif // ENUMS_H
