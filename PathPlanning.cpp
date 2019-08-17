
#include "PathPlanning.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

PathPlanning::PathPlanning(Grid maze, int rows, int cols) {
    this->maze = maze;
    this->columns = cols;
    this->rows = rows;
}

PathPlanning::~PathPlanning() {

}

void PathPlanning::initialPosition(int x, int y) {
    pdList = new PDList();
    pdList->addBack(new PositionDistance(x, y, 0));
}

PDList* PathPlanning::getReachablePositions() {
    //Let x be the starting position of the robot with distance 0
    //Let P be a list of positions the robot can reach, with distances (initially contains x)
    //Let T be a temporary list (initially empty)
    //repeat
    //| Select an item p from P that is not in T
    //| foreach Position, q that the robot can reach from p do
    //| | Set the distance of q to be one more than the distance of p
    //| | Add q to P if and only if there is no item in P with the same co-ordinate as q
    //| end
    //| Add p to T
    //until No such position p can be found

    PDList* tempList = new PDList();

    int count = 0;

    do {
        // Check if tempList contains
        if (!tempList->containsCoordinate(pdList->get(count))){
            // If it doesnt add it to it
            PDPtr position = pdList->get(count);

            checkAddPos(position->getX(), position->getY() + 1, position->getDistance());
            checkAddPos(position->getX(), position->getY() - 1, position->getDistance());
            checkAddPos(position->getX() + 1, position->getY(), position->getDistance());
            checkAddPos(position->getX() - 1, position->getY(), position->getDistance());

            tempList->addBack(position);
        }
        count++;
    } while (pdList->size() != tempList->size());

   return pdList;
}

void PathPlanning::checkAddPos(int x, int y, int distance) {
    if (maze[y][x] == '.') {
        auto position = new PositionDistance(x, y, distance + 1);
        if (!pdList->containsCoordinate(position)) {
            pdList->addBack(position);
        }
    }
}

// THIS IS FOR MILESTONE 3 ONLY
//    ONLY IMPLEMENT THIS IF YOU ATTEMPT MILESTONE 3
PDList* PathPlanning::getPath(int toX, int toY) {
   return NULL;
}
