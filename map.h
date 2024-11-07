#define GRIDROWS 15
#define GRIDCOLUMNS 20
#define CELLSIZE 50

void createGrid();
void createWalls();
void createBackground();
int isBlocked(int, int);
int isMarker(int, int);
void createMarker(int, int);
void createMultipleMarkers(int);
void drawMarker(int, int);
void destroyMarker(int, int);
void createObstacle();