
#include "PDList.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>


// Create a New Empty List
PDList::PDList() {
    numPositions = 0;
}

// Clean-up the list
PDList::~PDList() {
    // If
}

// Number of items in the list
int PDList::size() {
   return numPositions;
}

// Get a pointer to the position-distance at index i
PDPtr PDList::get(int i) {
   return positions[i];
}

// Add a position-distance (as a pointer) to the list
// This class now has control over the pointer
// And should delete the pointer if the position-distance is removed from the list
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

bool PDList::checkEquality(PDPtr posInList, PDPtr posProvided, char coord) {
    if (coord == 'x'){
        return posInList->getX() == posProvided->getX();
    } else if (coord == 'y'){
        return posInList->getY() == posProvided->getY();
    }
    return false;
}

// Remove everything from the list
void PDList::clear() {
}
