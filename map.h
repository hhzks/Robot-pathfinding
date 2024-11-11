#ifndef MAP_H
#define MAP_H

#define CELLSIZE 50

extern int gridRows;
extern int gridColumns;

enum direction {North, East, South, West};
typedef enum direction direction;

typedef struct {
    int row;
    int column;
    direction orientation;
    int markerCount;
    int **visitedMatrix;
} Robot;

typedef struct {
    int row;
    int column;
} Cell;

enum cellType {open, marker, obstacle, wall, home};
typedef enum cellType cellType;

void drawRobot(Robot *robot);
void drawMarker(int, int);
void clearMarker(int, int);
int isMarker(int, int);
int isBlocked(int, int);
int isHome(int, int);
int markersInGrid();
Cell chooseRandomOpenCell();
void createArena();
void freeArenaMemory();

#endif