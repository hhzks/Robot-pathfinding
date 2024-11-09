#define GRIDROWS 15
#define GRIDCOLUMNS 20
#define CELLSIZE 50

enum cellType {open, marker, obstacle, wall};
typedef enum cellType cellType;

void drawMarker(int,int);
void createMarker(int,int);
void destroyMarker(int,int);
int isBlocked(int, int);
int isMarker(int, int);
int isWall(int, int);
int isObstacle(int, int);
int isBlocked(int, int);
void createArena();