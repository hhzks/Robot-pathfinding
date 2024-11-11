#include "map.h"

#include <stdlib.h>
#include <time.h>

#include "graphics.h"

int gridColumns;
int gridRows;
int homeRow;
int homeColumn;
int **gridMatrix;

static void generateGridDimensions() {
    // The width and length of the grid is randomly chosen to be between 10 and 19 cells
    gridRows = rand() % 10 + 10;
    gridColumns = rand() % 10 + 10;
}

static void initializeGridMatrix() {
    gridMatrix = calloc(gridRows, sizeof(int *));
    for (int i = 0; i < gridRows; i++) {
        gridMatrix[i] = calloc(gridColumns, sizeof(int));
    }
}

static void createGrid(int screenWidth, int screenHeight) {
    setColour(black);
    for (int i = 1; i < gridRows; i++) {
        drawLine(0, i * CELLSIZE, screenWidth, i * CELLSIZE);
    }
    for (int i = 1; i < gridColumns; i++) {
        drawLine(i * CELLSIZE, 0, i * CELLSIZE, screenHeight);
    }
}

static int isCellType(cellType cellType, int row, int column) {
    if (gridMatrix[row][column] == cellType) {
        return 1;
    } else {
        return 0;
    }
}

void drawRobot(Robot *robot) {
    setColour(green);
    int *xCoords = malloc(sizeof(int) * 3);
    int *yCoords = malloc(sizeof(int) * 3);
    switch (robot->orientation) {
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
            xCoords[1] = (robot->column + 1) * CELLSIZE;
            xCoords[2] = (robot->column + 1) * CELLSIZE;
            yCoords[0] = (robot->row * CELLSIZE) + (CELLSIZE / 2);
            yCoords[1] = robot->row * CELLSIZE;
            yCoords[2] = (robot->row + 1) * CELLSIZE;
            break;
    }
    fillPolygon(3, xCoords, yCoords);
    free(xCoords);
    free(yCoords);
}

static void drawMarkerBackground(int row, int column) {
    setColour(orange);
    fillOval(column * CELLSIZE, row * CELLSIZE, CELLSIZE, CELLSIZE);
}

void drawMarker(int row, int column) {
    setColour(yellow);
    fillOval((column + 0.25) * CELLSIZE, (row + 0.25) * CELLSIZE, 0.5 * CELLSIZE, 0.5 * CELLSIZE);
}

static void createMarker(int row, int column) {
    gridMatrix[row][column] = marker;
    drawMarkerBackground(row, column);
}

void clearMarker(int row, int column) {
    gridMatrix[row][column] = open;
}

int isMarker(int row, int column) {
    return isCellType(marker, row, column);
}

static int isOpen(int cell, int column) {
    return isCellType(open, cell, column);
}

static void drawObstacle(int row, int column) {
    setColour(darkgray);
    fillRect(column * CELLSIZE, row * CELLSIZE, CELLSIZE, CELLSIZE);
}

static void createObstacle(int row, int column) {
    gridMatrix[row][column] = obstacle;
    drawObstacle(row, column);
}

static int isObstacle(int row, int column) {
    return isCellType(obstacle, row, column);
}

static int isWall(int row, int column) {
    return (isCellType(wall, row, column));
}

int isBlocked(int row, int column) {
    return (isObstacle(row, column) || isWall(row, column));
}

static void drawHome(int row, int column) {
    setColour(cyan);
    fillRect(column * CELLSIZE, row * CELLSIZE, CELLSIZE, CELLSIZE);
}

static void createHome(int row, int column) {
    gridMatrix[row][column] = home;
    drawHome(row, column);
}

int isHome(int row, int column) {
    return isCellType(home, row, column);
}

static void closeDisconnectedCells(int homeRow, int homeColumn) {
    /*    - This is called once the random walls have been generated
          - This function uses bfs to find all the accessible cells from the home cell,
            then 'closes off' any inaccessible tiles so that markers/obstacles don't spawn there */

    Cell *queue = malloc(sizeof(Cell) * gridRows * gridColumns);
    Cell *front = queue;
    Cell *rear = queue;

    int **visitedMatrix = calloc(gridRows, sizeof(int *));
    for (int i = 0; i < gridRows; i++) {
        visitedMatrix[i] = calloc(gridColumns, sizeof(int));
    }

    Cell homeCell = {homeRow, homeColumn};
    *rear = homeCell;
    rear++;
    visitedMatrix[homeRow][homeColumn] = 1;

    while (front != rear) {
        Cell currentCell = *front;
        front++;
        // note: we don't have to worry about array indexing being out of bounds because wall cells are guaranteed to be on the edges of the grid
        if (visitedMatrix[currentCell.row - 1][currentCell.column] == 0 && !(isWall(currentCell.row - 1, currentCell.column))) {
            if (!isObstacle(currentCell.row - 1, currentCell.column)) {
                Cell newCell = {currentCell.row - 1, currentCell.column};
                *rear = newCell;
                rear++;
            }
            // if we encounter an obstacle we don't add it to the queue, but we still mark it as visited to not associate it with being a wall
            visitedMatrix[currentCell.row - 1][currentCell.column] = 1;
        }
        if (visitedMatrix[currentCell.row + 1][currentCell.column] == 0 && !(isWall(currentCell.row + 1, currentCell.column))) {
            if (!isObstacle(currentCell.row + 1, currentCell.column)) {
                Cell newCell = {currentCell.row + 1, currentCell.column};
                *rear = newCell;
                rear++;
            }
            visitedMatrix[currentCell.row + 1][currentCell.column] = 1;
        }
        if (visitedMatrix[currentCell.row][currentCell.column - 1] == 0 && !(isWall(currentCell.row, currentCell.column - 1))) {
            if (!isObstacle(currentCell.row, currentCell.column - 1)) {
                Cell newCell = {currentCell.row, currentCell.column - 1};
                *rear = newCell;
                rear++;
            }
            visitedMatrix[currentCell.row][currentCell.column - 1] = 1;
        }
        if (visitedMatrix[currentCell.row][currentCell.column + 1] == 0 && !(isWall(currentCell.row, currentCell.column + 1))) {
            if (!isObstacle(currentCell.row, currentCell.column + 1)) {
                Cell newCell = {currentCell.row, currentCell.column + 1};
                *rear = newCell;
                rear++;
            }
            visitedMatrix[currentCell.row][currentCell.column + 1] = 1;
        }
    }

    for (int i = 0; i < gridRows; i++) {
        for (int j = 0; j < gridColumns; j++) {
            if (visitedMatrix[i][j] == 0) {
                gridMatrix[i][j] = wall;
            }
        }
    }

    free(queue);
    for (int i = 0; i < gridRows; i++) {
        free(visitedMatrix[i]);
    }
    free(visitedMatrix);
}

static void drawWalls() {
    setColour(red);
    for (int i = 0; i < gridRows; i++) {
        for (int j = 0; j < gridColumns; j++) {
            if (gridMatrix[i][j] == wall) {
                fillRect(j * CELLSIZE, i * CELLSIZE, CELLSIZE, CELLSIZE);
            }
        }
    }
}

static void createWalls(int screenWidth, int screenHeight) {
    // initial boundary walls
    for (int i = 0; i < gridRows; i++) {
        gridMatrix[i][0] = wall;
        gridMatrix[i][gridColumns - 1] = wall;
    }
    for (int i = 0; i < gridColumns; i++) {
        gridMatrix[0][i] = wall;
        gridMatrix[gridRows - 1][i] = wall;
    }

    // scan the grid and randomly place walls if the cell is adjacent to a wall
    for (int i = 1; i < gridRows - 1; i++) {
        for (int j = 1; j < gridColumns - 1; j++) {
            if (rand() % 2 == 0 && (gridMatrix[i + 1][j] == wall || gridMatrix[i - 1][j] == wall || gridMatrix[i][j + 1] == wall || gridMatrix[i][j - 1] == wall) && gridMatrix[i][j] != home) {
                gridMatrix[i][j] = wall;
                fillRect(j * CELLSIZE, i * CELLSIZE, CELLSIZE, CELLSIZE);
            }
        }
    }

    closeDisconnectedCells(homeRow, homeColumn);
    drawWalls();
}

static void createMultipleObjects(cellType cellType, int noOfObjects) {
    int objectsCreated = 0;
    int failedAttempts = 0;
    while (objectsCreated < noOfObjects && failedAttempts < 100) {
        int randomRow = rand() % gridRows;
        int randomColumn = rand() % gridColumns;
        if (!(isMarker(randomRow, randomColumn) || isBlocked(randomRow, randomColumn) || isHome(randomRow, randomColumn))) {
            switch (cellType) {
                case marker:
                    createMarker(randomRow, randomColumn);
                    break;
                case obstacle:
                    createObstacle(randomRow, randomColumn);
                    break;
                default:
                    // only marker and obstacle types should call this function
                    return;
            }
            objectsCreated++;
        } else {
            failedAttempts++;  // prevents infinite loop if there are no more open cells
        }
    }
}

static void createMultipleMarkers(int noOfMarkers) {
    createMultipleObjects(marker, noOfMarkers);
}

int markersInGrid() {
    int markerCount = 0;
    for (int i = 0; i < gridRows; i++) {
        for (int j = 0; j < gridColumns; j++) {
            if (isMarker(i, j)) {
                markerCount++;
            }
        }
    }
    return markerCount;
}

static void createMultipleObstacles(int noOfObstacles) {
    createMultipleObjects(obstacle, noOfObstacles);
}

Cell chooseRandomOpenCell() {
    Cell openCell;
    do {
        openCell.row = rand() % gridRows;
        openCell.column = rand() % gridColumns;
    } while (!isOpen(openCell.row, openCell.column));
    return openCell;
}

static void createBackground(int screenWidth, int screenHeight) {
    setWindowSize(screenWidth, screenHeight);
    background();
    createGrid(screenWidth, screenHeight);
    homeRow = gridRows / 2 + 1;  // home cell is placed in the middle of the grid
    homeColumn = gridColumns / 2 + 1;
    createHome(homeRow, homeColumn);
    createMultipleObstacles(20);
    createWalls(screenWidth, screenHeight);
    createMultipleMarkers(10);
    setColour(blue);
    foreground();
}

void createArena() {
    srand(time(NULL));
    generateGridDimensions();
    initializeGridMatrix();
    int screenWidth = gridColumns * CELLSIZE;
    int screenHeight = gridRows * CELLSIZE;
    createBackground(screenWidth, screenHeight);
}

void freeArenaMemory() {
    for (int i = 0; i < gridRows; i++) {
        free(gridMatrix[i]);
    }
    free(gridMatrix);
}