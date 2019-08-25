
#include "PDList.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

// Create a New Empty List (capable of holding only as many positions that can have a value as necessary (no borders)
PDList::PDList(int rows, int columns) : ROWS(rows - BORDERS), COLUMNS(columns - BORDERS) {
    positions = new PDPtr [LENGTH];
    numPositions = 0;
    for (int i = 0; i != LENGTH; i++) {
        positions[i] = nullptr;
    }
}

PDList::PDList(PDList &list, int rows, int columns) : ROWS(rows - 2), COLUMNS(columns - 2) {
    positions = new PDPtr [LENGTH];
    this->numPositions = list.numPositions;
    for (int i = 0; i < LENGTH; ++i) {
        if (list.positions[i] != nullptr) {
            this->positions[i] = new PositionDistance(list.positions[i]->getX(),
                    list.positions[i]->getY(), list.positions[i]->getDistance());
        } else {
            positions[i] = nullptr;
        }

    }
}

// Clean-up the list
PDList::~PDList() {
    clear();
}

// Number of items in the list
int PDList::size() {
   return numPositions;
}

// Get a pointer to the position-distance at index i
PDPtr PDList::get(int i) {
   return positions[i];
}

/*
 * Add a position-distance (as a pointer) to the list
 * This class now has control over the pointer
 * And should delete the pointer if the position-distance is removed from the list
 */
void PDList::addBack(PDPtr position) {
    positions[numPositions] = position;
    numPositions++;
}

// Checks if the list contains a position-distance with the same co-ordinate
// as the given position.
bool PDList::containsCoordinate(PDPtr position) {
    // Check all position that have a value
    for (int i = 0; i < numPositions; ++i) {
        // If Y matches check X if not, dont bother
        if (checkEquality(positions[i], position, 'y')){
            if (checkEquality(positions[i], position, 'x')){
                return true;
            }
        }
    }
    return false;
}

// Compares coordinates of two different PDPtr lists and returns true if their values are equal
bool PDList::checkEquality(PDPtr posInList, PDPtr posProvided, char coord) {
    if (coord == 'x'){
        return posInList->getX() == posProvided->getX();
    } else if (coord == 'y'){
        return posInList->getY() == posProvided->getY();
    }
    return false;
}

// removes starting position from the list and moves pointers
void PDList::resizeArray(){
    delete positions[0];
    positions[0] = nullptr;
    for (int j = 0; j < numPositions; ++j) {
        positions[j] = positions[j + 1];
    }
    positions[numPositions] = nullptr;
    --numPositions;
}

// Remove everything from the list
void PDList::clear() {
    for (int i = 0; i != LENGTH; ++i) {
        if (positions[i] != nullptr) {
            delete positions[i];
            positions[i] = nullptr;
        }
    }
}
