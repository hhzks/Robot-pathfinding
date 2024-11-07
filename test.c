#include "graphics.h"
#include "map.h"
#include "stdio.h"
#include "robot.h"

void updateScreen(Robot *robot){
    clear();
    drawRobot(robot);
    for (int i = 0; i < GRIDROWS; i++){
        for (int j = 0; j < GRIDCOLUMNS; j++){
            if (isMarker(i,j)){
                drawMarker(i,j);
            }
        }
    }
}

void turnAround(Robot *robot){
    left(robot);
    left(robot);
}

int main(){
    createBackground();
    Robot aRobot = {5,5,North};
    Robot *pRobot = &aRobot;
    createMultipleMarkers(20);
    for(int i = 0; i < 1000; i++){
        if (atMarker(pRobot)){
            pickUpMarker(pRobot);
        }

        if(canMoveForward(pRobot)){
            forward(pRobot);
        }
        else{
            left(pRobot);
            updateScreen(pRobot);
            sleep(100);
            forward(pRobot);
            updateScreen(pRobot);
            sleep(100);
            left(pRobot);
        }
        updateScreen(pRobot);
        sleep(100);
    }
    return 0;
}