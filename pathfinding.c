#include "pathfinding.h"

#include <stdio.h>
#include <stdlib.h>

#include "animation.h"
#include "graphics.h"
#include "map.h"
#include "robot.h"

void initialiseRobotMemory(Robot *robot) {
    robot->visitedMatrix = calloc(gridRows, sizeof(int *));
    for (int i = 0; i < gridRows; i++) {
        robot->visitedMatrix[i] = calloc(gridColumns, sizeof(int));
    }
}

void freeRobotMemory(Robot *robot) {
    for (int i = 0; i < gridRows; i++) {
        free(robot->visitedMatrix[i]);
    }
    free(robot->visitedMatrix);
}

static void turnAround(Robot *robot) {
    right(robot);
    updateScreen(robot);
    sleep(DELTATIME);
    right(robot);
    updateScreen(robot);
}

static void turnToDirection(Robot *robot, direction desiredDirection) {
    int difference = (robot->orientation - desiredDirection) % 4;
    switch (difference) {
        case 0:
            break;
        case 1:
            left(robot);
            updateScreen(robot);
            break;
        case 2:
            turnAround(robot);
            break;
        case 3:
            right(robot);
            updateScreen(robot);
            break;
    }
}

static int cellInFrontVisited(Robot *robot) {
    switch (robot->orientation) {
        case North:
            if (robot->visitedMatrix[robot->row - 1][robot->column] != 0) {
                return 1;
            } else {
                return 0;
            }
            break;
        case South:
            if (robot->visitedMatrix[robot->row + 1][robot->column] != 0) {
                return 1;
            } else {
                return 0;
            }
            break;
        case East:
            if (robot->visitedMatrix[robot->row][robot->column + 1] != 0) {
                return 1;
            } else {
                return 0;
            }
            break;
        case West:
            if (robot->visitedMatrix[robot->row][robot->column - 1] != 0) {
                return 1;
            } else {
                return 0;
            }
            break;
    }
    return 0;
}

static direction *dfs(Robot *robot, int totalMarkers, direction *homeStack) {
    // this stack stores moves that were made to get to the current cell
    // pop from the stack to get back to the previous cell
    direction *stack = malloc(gridRows * gridColumns * sizeof(direction));
    direction *bottom = stack;
    direction *top = stack;

    direction *topOfhomeStack = homeStack;

    direction initialMove = robot->orientation;
    *top = initialMove;
    top++;

    // 1: True, 0: False
    int moveFound = 1;
    int homeCellFound = 0;
    while ((bottom != top && markerCount(robot) < totalMarkers) || !homeCellFound) {
        if (!moveFound) {
            // move to the previous cell
            direction currentDirection = *(--top);
            turnToDirection(robot, (currentDirection + 2) % 4);
            updateScreen(robot);
            sleep(DELTATIME);
            forward(robot);
        }

        if (homeCellFound) {
            *topOfhomeStack = (robot->orientation + 2) % 4;
            topOfhomeStack++;
        }

        if (atMarker(robot)) {
            pickUpMarker(robot);
        }

        updateScreen(robot);
        sleep(DELTATIME);

        moveFound = 0;
        for (int i = 0; i < 4; i++) {
            if (canMoveForward(robot) && !cellInFrontVisited(robot)) {
                moveFound = 1;
                forward(robot);
                direction newMove = robot->orientation;
                *top = newMove;
                top++;
                if (isAtHome(robot)) {
                    robot->visitedMatrix[robot->row][robot->column] = 2;
                    homeCellFound = 1;
                } else {
                    robot->visitedMatrix[robot->row][robot->column] = 1;
                }
                break;
            }
            right(robot);
            updateScreen(robot);
            sleep(DELTATIME);
        }
    }

    // add the final move to the stack
    *topOfhomeStack = (robot->orientation + 2) % 4;
    topOfhomeStack++;

    free(stack);

    return topOfhomeStack;
}

static void returnHome(Robot *robot, direction *currentMoveToHomeCell) {
    while (!isAtHome(robot)) {
        turnToDirection(robot, *currentMoveToHomeCell--);
        sleep(DELTATIME);
        forward(robot);
        updateScreen(robot);
        sleep(DELTATIME);
    }
    free(currentMoveToHomeCell);
}

void findMarkersAndGoHome(Robot *robot, int totalMarkers) {
    direction *homeStack = calloc(4 * gridRows * gridColumns, sizeof(direction));  // this stack is used to store the moves to get back to the home cell
    direction *currentMoveToHomeCell = dfs(robot, totalMarkers, homeStack);        // at most there will be 4 moves per cell, so the stack will be twice the size of the grid
    returnHome(robot, currentMoveToHomeCell);
    free(homeStack);
}