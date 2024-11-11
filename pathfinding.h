#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "map.h"

void updateScreen(Robot *robot);
void initialiseRobotMemory(Robot *robot);
void freeRobotMemory(Robot *robot);
void findMarkersAndGoHome(Robot *robot, int);
#endif