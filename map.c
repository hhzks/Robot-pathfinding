#include "map.h"
#include "graphics.h"
#include "stdlib.h"
#include "time.h"

int screenWidth = CELLSIZE * GRIDCOLUMNS;
int screenHeight = CELLSIZE * GRIDROWS;
int gridMatrix[GRIDROWS][GRIDCOLUMNS];

void createGrid(){
    setColour(black);
    for (int i = 1; i < GRIDROWS; i++){
        drawLine(0,i*CELLSIZE,screenWidth,i*CELLSIZE);
    }
    for (int i = 1; i < GRIDCOLUMNS; i++){
        drawLine(i*CELLSIZE,0,i*CELLSIZE,screenHeight);
    }
}

void createWalls(){
    setColour(red);
    for (int i = 0; i < GRIDROWS; i++){
        fillRect(0,i*CELLSIZE,CELLSIZE,(i+1)*CELLSIZE);
        gridMatrix[i][0] = 3;
        fillRect(screenWidth-CELLSIZE,i*CELLSIZE,screenWidth,(i+1)*CELLSIZE);
        gridMatrix[i][GRIDCOLUMNS-1] = 3;
    }
    for (int i = 0; i < GRIDCOLUMNS; i++){
        fillRect(i*CELLSIZE,0,(i+1)*CELLSIZE,CELLSIZE);
        gridMatrix[0][i] = 3;
        fillRect(i*CELLSIZE,screenHeight-CELLSIZE,(i+1)*CELLSIZE,screenHeight);
        gridMatrix[GRIDROWS-1][i] = 3;
    }
}

void createBackground(){
    setWindowSize(screenWidth, screenHeight);
    background();
    createGrid();
    createWalls();
    foreground();
}


int isBlocked(int row,int column){
    if (gridMatrix[row][column] > 1){
        return 1;
    }
    else{
        return 0;
    }
}

int isMarker(int row, int column){
    if (gridMatrix[row][column] == 1){
        return 1;
    }
    else{
        return 0;
    }
}

void createMarker(int row, int column){
    gridMatrix[row][column] = 1;
    drawMarker(row, column);
}

void createMultipleMarkers(int noOfMarkers){
    srand(time(NULL));
    int markersCreated = 0;
    while (markersCreated < noOfMarkers){
        int randomRow = rand() % GRIDROWS;
        int randomColumn = rand() % GRIDCOLUMNS;
        if (!(isMarker(randomRow, randomColumn) || isBlocked(randomRow, randomColumn))){
            createMarker(randomRow, randomColumn);
            markersCreated++;
        }
    }
}

void destroyMarker(int row, int column){
    gridMatrix[row][column] = 0;
}

void drawMarker(int row, int column){
    setColour(darkgray);
    fillOval(column*CELLSIZE, row*CELLSIZE, CELLSIZE, CELLSIZE);
    setColour(magenta);
    fillOval((column+0.25)*CELLSIZE, (row+0.25)*CELLSIZE, 0.5*CELLSIZE, 0.5*CELLSIZE);
}
