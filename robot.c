#include "robot.h"

void forward(Robot *robot) {
    if (canMoveForward(robot)) {
        switch (robot->orientation) {
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
}

void left(Robot *robot) {
    robot->orientation = (robot->orientation - 1) % 4;
}

void right(Robot *robot) {
    robot->orientation = (robot->orientation + 1) % 4;
}

int atMarker(Robot *robot) {
    return isMarker(robot->row, robot->column);
}

int canMoveForward(Robot *robot) {
    switch (robot->orientation) {
        case North:
            if (isBlocked(robot->row - 1, robot->column)) {
                return 0;
            } else {
                return 1;
            }
            break;
        case South:
            if (isBlocked(robot->row + 1, robot->column)) {
                return 0;
            } else {
                return 1;
            }
            break;
        case East:
            if (isBlocked(robot->row, robot->column + 1)) {
                return 0;
            } else {
                return 1;
            }
            break;
        case West:
            if (isBlocked(robot->row, robot->column - 1)) {
                return 0;
            } else {
                return 1;
            }
            break;
    }
    return 0;
}

void pickUpMarker(Robot *robot) {
    robot->markerCount++;
    clearMarker(robot->row, robot->column);
}

void dropMarker(Robot *robot) {
    robot->markerCount--;
    drawMarker(robot->row, robot->column);
}

int markerCount(Robot *robot) {
    return robot->markerCount;
}

int isAtHome(Robot *robot) {
    return isHome(robot->row, robot->column);
}