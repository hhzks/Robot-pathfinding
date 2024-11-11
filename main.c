#include <stdlib.h>

#include "animation.h"
#include "graphics.h"
#include "map.h"
#include "pathfinding.h"
#include "robot.h"

int main() {
    createArena();
    int totalMarkers = markersInGrid();
    Cell randomCell = chooseRandomOpenCell();
    direction randomDirection = rand() % 4;
    Robot aRobot = {randomCell.row, randomCell.column, randomDirection};
    Robot *pRobot = &aRobot;
    initialiseRobotMemory(pRobot);
    findMarkersAndGoHome(pRobot, totalMarkers);
    dropMarker(pRobot);
    sleep(1000);
    freeArenaMemory(pRobot);
    freeRobotMemory(pRobot);
    return 0;
}