
#include "PositionDistance.h"

PositionDistance::PositionDistance(int x, int y, int distance) : x(x), y(y), distance(distance)
{}

int PositionDistance::getX() {
   return x;
}

int PositionDistance::getY() {
   return y;
}

int PositionDistance::getDistance() {
   return distance;
}
