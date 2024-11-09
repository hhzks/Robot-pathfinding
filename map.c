#include "map.h"
#include "graphics.h"
#include "stdlib.h"
#include "time.h"

int screenWidth = CELLSIZE * GRIDCOLUMNS;
int screenHeight = CELLSIZE * GRIDROWS;
int gridMatrix[GRIDROWS][GRIDCOLUMNS];

static void createGrid(){
    setColour(black);
    for (int i = 1; i < GRIDROWS; i++){
        drawLine(0,i*CELLSIZE,screenWidth,i*CELLSIZE);
    }
    for (int i = 1; i < GRIDCOLUMNS; i++){
        drawLine(i*CELLSIZE,0,i*CELLSIZE,screenHeight);
    }
}

static void createWalls(){
    setColour(red);
    for (int i = 0; i < GRIDROWS; i++){
        fillRect(0,i*CELLSIZE,CELLSIZE,(i+1)*CELLSIZE);
        gridMatrix[i][0] = wall;
        fillRect(screenWidth-CELLSIZE,i*CELLSIZE,screenWidth,(i+1)*CELLSIZE);
        gridMatrix[i][GRIDCOLUMNS-1] = wall;
    }
    for (int i = 0; i < GRIDCOLUMNS; i++){
        fillRect(i*CELLSIZE,0,(i+1)*CELLSIZE,CELLSIZE);
        gridMatrix[0][i] = wall;
        fillRect(i*CELLSIZE,screenHeight-CELLSIZE,(i+1)*CELLSIZE,screenHeight);
        gridMatrix[GRIDROWS-1][i] = wall;
    }
}

static int isCellType(cellType cellType, int row, int column){
    if (gridMatrix[row][column] == cellType){
        return 1;
    }
    else{
        return 0;
    }
}

void drawMarker(int row, int column){
    setColour(orange);
    fillOval(column*CELLSIZE, row*CELLSIZE, CELLSIZE, CELLSIZE);
    setColour(yellow);
    fillOval((column+0.25)*CELLSIZE, (row+0.25)*CELLSIZE, 0.5*CELLSIZE, 0.5*CELLSIZE);
}

void createMarker(int row, int column){
    gridMatrix[row][column] = marker;
    drawMarker(row,column);
}

void destroyMarker(int row, int column){
    gridMatrix[row][column] = open;
}


static void drawObstacle(int row, int column){
    setColour(darkgray);
    fillRect(column*CELLSIZE, row*CELLSIZE, CELLSIZE, CELLSIZE);
}

static void createObstacle(int row, int column){
    gridMatrix[row][column] = obstacle;
    drawObstacle(row,column);
}

int isMarker(int row, int column){
    return isCellType(marker, row, column);
}

int isObstacle(int row, int column){
    return isCellType(obstacle, row, column);
}

int isWall(int row, int column){
    return (isCellType(wall, row, column));
}

int isBlocked(int row,int column){
    return (isObstacle(row, column) || isWall(row,column));  
}

static void createMultipleObjects(cellType cellType, int noOfMarkers){
    int objectsCreated = 0;
    while (objectsCreated < noOfMarkers){
        int randomRow = rand() % GRIDROWS;
        int randomColumn = rand() % GRIDCOLUMNS;
        if (!(isMarker(randomRow, randomColumn) || isBlocked(randomRow, randomColumn))){
            switch (cellType){
                case marker:
                    createMarker(randomRow, randomColumn);
                    break;
                case obstacle:
                    createObstacle(randomRow, randomColumn);
                    break;
                default:
                    //Only marker or obstacle should be passed in for cell type; if we reach this point then something has gone wrong
                    return;
            }
            objectsCreated++;
        }
    }
}

static void createMultipleMarkers(int noOfMarkers){
    createMultipleObjects(marker, noOfMarkers);
}

static void createMultipleObstacles(int noOfObstacles){
    createMultipleObjects(obstacle, noOfObstacles);
}

static void createBackground(){
    setWindowSize(screenWidth, screenHeight);
    background();
    createGrid();
    createWalls();
    createMultipleObstacles(rand()%30);
    foreground();
}

void createArena(){
    createBackground();
    createMultipleMarkers(rand()%30);
}