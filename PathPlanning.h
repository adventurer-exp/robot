
#ifndef COSC_ASS_ONE_PATH_PLANNING
#define COSC_ASS_ONE_PATH_PLANNING

#include "PositionDistance.h"
#include "PDList.h"
#include "Types.h"

#define DIRECTIONS 4


class PathPlanning {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */


   // Initialise a with a given maze of size (x,y)
   PathPlanning(Grid maze, int rows, int cols);

   // Clean-up
   ~PathPlanning();

   // The initial position
   void initialPosition(int x, int y);

   // Method for Milestone 2
   // Return a DEEP COPY of the PDList of all position-distance's
   //    that the robot can reach
   PDList* getReachablePositions();


   // Method for Milestone 3
   // Get the path from the starting position to the given co-ordinate
   //    The path should be a DEEP COPY
   PDList* getPath(int toX, int toY);


   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */


private:
    void checkAddPos(int x, int y, int distance, PDList* pdList);

    PDList* list;
    Grid maze;
    int rows, columns, x, y;

    PDPtr findPosition(int x, int y);

    bool getNextStep(int toX, int toY, int distance);
};

#endif // COSC_ASS_ONE_PATH_PLANNING
