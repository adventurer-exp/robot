
#include "PathPlanning.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

#define XPOS position->getX()
#define YPOS position->getY()
#define POS_DIST position->getDistance()

/*
 * I tried to make the program as simple as I could
 *
 * Issues
 * returning an array without first value
 * Simple algorithm on checking the surroundings ( 0 1, 0 -1, 1 0, -1 0)
 * Hard copying positions to temp array instead of just adding pointer
 *
 * Pros and Cons
 * - When cutting the array in order to return it, if it comes to filling the whole positions array, I would lose last value
 * I believe there must be a more efficient way of checking the surroundings however I couldn't come up with anything simpler
 * If PD List needed again with starting position, that would not be possible
 * Never using size of the maze
 *
 * + when creating Lists, all values in array are set to null to avoid errors
 * When searching through position, examining only positions that are filled with values and not the whole array
 * When looking up matching coordinates, if one doesn't match, it is not needed to check the other one because it is clear
 * they are not equal
 * #defines for for some long expressions to increase readability
 *
 */

PathPlanning::PathPlanning(Grid maze, int rows, int cols) {
    this->maze = maze;
    this->columns = cols;
    this->rows = rows;
}

PathPlanning::~PathPlanning() {
}

void PathPlanning::initialPosition(int x, int y) {
    this->x = x;
    this->y = y;
    // Adds an initial position
}

PDList* PathPlanning::getReachablePositions() {
    auto* tempList = new PDList();
    PDList* posDistances = new PDList();

    posDistances->addBack(new PositionDistance(x, y, 0));

    int count = 0;

    do {
        // Check if tempList contains
        if (!tempList->containsCoordinate(posDistances->get(count))){
            // If it doesnt add it to it
            PDPtr position = posDistances->get(count);

            // Do a loop (check) for surrounding fields (x +- 1, y +- 1)
            int xCoord = 1, yCoord = 1;
            for (int i = 0; i < DIRECTIONS/2; ++i) {
                // Pass in current position and change x, y
                checkAddPos(XPOS, YPOS + yCoord, POS_DIST, posDistances);
                checkAddPos(XPOS + xCoord, YPOS, POS_DIST, posDistances);
                xCoord = -xCoord;
                yCoord = -yCoord;
            }
            // Adds position that has been checked into the temporary list
            tempList->addBack(new PositionDistance(XPOS, YPOS, POS_DIST));
        }
        count++;
        // stops the loop when temporary list reaches the same amount of objects as pdList
    } while (posDistances->size() != tempList->size());
    posDistances->resizeArray();
    tempList->resizeArray();
    list = tempList;
    return posDistances;
}

// Checks if required field is accessible ('.'), if so, checks if it already is in PDList
// and in case it is not, adds it there with distance 1 bigger than current position
void PathPlanning::checkAddPos(int x, int y, int distance, PDList* pdList) {
    if (maze[y][x] == '.') {
        auto position = new PositionDistance(x, y, distance + 1);
        if (!pdList->containsCoordinate(position)) {
            pdList->addBack(position);
        }
    }
}

// THIS IS FOR MILESTONE 3 ONLY
//    ONLY IMPLEMENT THIS IF YOU ATTEMPT MILESTONE 3

/*
 * Find coordinate in list I used to find reachable positions
 * check available surroundings and pick the first one with distance - 1 than current
 * add the previous one to the list and change my current one to the new one
 * repeat until you are standing on the one with distance 1
 * add x and y variables with distance 0
 * return path
 */
PDList* PathPlanning::getPath(int toX, int toY) {
    PDList* path = new PDList();
    PDPtr position =  findPosition(toX, toY);
    path->addBack(position);
    int distance = position->getDistance();

    while (distance != 1){
        if (maze[toY + 1][toX] == '.' && findPosition(toX, toY + 1)->getDistance() == distance - 1) {
            toY++;
        } else if (maze[toY - 1][toX] == '.'&& findPosition(toX, toY - 1)->getDistance() == distance - 1) {
            toY--;
        } else if (maze[toY][toX + 1] == '.' && findPosition(toX + 1, toY)->getDistance() == distance - 1){
            toX++;
        } else {
            toX--;
        }
        --distance;
        path->addBack(new PositionDistance(toX, toY, distance));
    }

    return path;
}

PDPtr PathPlanning::findPosition(int x, int y) {
    for (int i = 0; i < list->size(); i++){
        if (list->get(i)->getX() == x && list->get(i)->getY() == y){
            return list->get(i);
        }
    }
}
