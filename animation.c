#include "animation.h"

#include "graphics.h"

void updateScreen(Robot *robot) {
    clear();
    drawRobot(robot);
    for (int i = 0; i < gridRows; i++) {
        for (int j = 0; j < gridColumns; j++) {
            if (isMarker(i, j)) {
                drawMarker(i, j);
            }
        }
    }
}