#ifndef ROBOT_H
#define ROBOT_H

#include "map.h"

void forward(Robot *robot);
void left(Robot *robot);
void right(Robot *robot);
int atMarker(Robot *robot);
int canMoveForward(Robot *robot);
void pickUpMarker(Robot *robot);
void dropMarker(Robot *robot);
int markerCount(Robot *robot);
int isAtHome(Robot *robot);

#endif