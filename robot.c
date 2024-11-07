#include "graphics.h"
#include "robot.h"
#include "map.h"
#include "stdlib.h"
#include "stdio.h"

/*Notes:
It's probably best if we define grid / cell size as a constant somewhere so that it isn't dependent on anything idk
Memory should contain a stack to perform DFS
Also require a visited list. This will have at most m * n elements (obviously)
At most there's only gonna be 2(m+n-2) positions in the stack where m * n is the grid size, therefore we can define the stack to have max size 2(m+n-2)
Backwards isn't allowed in the robot implementation, create it as a separate function in main.c (needed for backtracking)

Learn how to format C cos i lowkey forgot
*/

void drawRobot(Robot *robot){
    setColour(green);
    int *xCoords = malloc(sizeof(int) * 3);
    int *yCoords = malloc(sizeof(int) * 3);
    switch(robot->orientation){
        case North:
            xCoords[0] = (robot->column * CELLSIZE) + (CELLSIZE / 2);
            xCoords[1] = robot->column * CELLSIZE;
            xCoords[2] = (robot->column + 1) * CELLSIZE;
            yCoords[0] = robot->row * CELLSIZE;
            yCoords[1] = (robot->row + 1) * CELLSIZE;
            yCoords[2] = (robot->row + 1) * CELLSIZE;
            break;
        case East:
            xCoords[0] = (robot->column + 1) * CELLSIZE;
            xCoords[1] = (robot->column) * CELLSIZE;
            xCoords[2] = (robot->column) * CELLSIZE;
            yCoords[0] = (robot->row * CELLSIZE) + (CELLSIZE / 2);
            yCoords[1] = robot->row * CELLSIZE;
            yCoords[2] = (robot->row + 1) * CELLSIZE;
            break;
        case South:
            xCoords[0] = (robot->column * CELLSIZE) + (CELLSIZE / 2);
            xCoords[1] = robot->column * CELLSIZE;
            xCoords[2] = (robot->column + 1) * CELLSIZE;
            yCoords[0] = (robot->row + 1) * CELLSIZE;
            yCoords[1] = (robot->row) * CELLSIZE;
            yCoords[2] = (robot->row) * CELLSIZE;
            break;
        case West:
            xCoords[0] = (robot->column) * CELLSIZE;
            xCoords[1] = (robot->column+1) * CELLSIZE;
            xCoords[2] = (robot->column+1) * CELLSIZE;
            yCoords[0] = (robot->row * CELLSIZE) + (CELLSIZE / 2);
            yCoords[1] = robot->row * CELLSIZE;
            yCoords[2] = (robot->row + 1) * CELLSIZE;
            break;
    }
    fillPolygon(3,xCoords,yCoords);
    free(xCoords);
    free(yCoords);
}

void forward(Robot *robot){
    switch(robot->orientation){
        case North:
            robot->row--;
            break;
        case South:
            robot->row++;
            break;
        case East:
            robot->column++;
            break;
        case West:
            robot->column--;
            break;
    }
}

//left and right functions cycle through the compass points in anticlockwise and clockwise directions respectively 
void left(Robot *robot){
    robot->orientation = (robot->orientation - 1) % 4;
}

void right(Robot *robot){
    robot->orientation = (robot->orientation + 1) % 4;
}

int atMarker(Robot *robot){
    return isMarker(robot->row,robot->column);
}

int canMoveForward(Robot *robot){
    switch(robot->orientation){
        case North:
            if (isBlocked(robot->row - 1,robot->column)){
                return 0;
            }
            else{
                return 1;
            }
            break;
        case South:
            if (isBlocked(robot->row + 1, robot->column)){
                return 0;
            }
            else{
                return 1;
            }
            break;
        case East:
            if (isBlocked(robot->row,robot->column + 1)){
                return 0;
            }
            else{
                return 1;
            }
            break;
        case West:
            if (isBlocked(robot->row,robot->column - 1)){
                return 0;
            }
            else{
                return 1;
            }
            break;
    }
    return 0;
}

void pickUpMarker(Robot *robot){
    robot->markerCount++;
    destroyMarker(robot->row,robot->column);
}

void dropMarker(Robot *robot){
    robot->markerCount--;
    createMarker(robot->row, robot->column);
}

int markerCount(Robot *robot){
    return robot->markerCount;
}