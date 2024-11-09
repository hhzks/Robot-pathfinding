/*typedef struct{
    int value;
    Node* right;
    Node* left;
    Node* above;
    Node* below;
}Node;*/

enum direction {North, East, South, West};
typedef enum direction direction;

typedef struct{
    int row;
    int column;
    direction orientation;
    int markerCount;
} Robot;

//typedef struct Robot Robot;

void drawRobot(Robot *robot);
void forward(Robot *robot);
void left(Robot *robot);
void right(Robot *robot);
int atMarker(Robot *robot);
int canMoveForward(Robot *robot);
void pickUpMarker(Robot *robot);
void dropMarker(Robot *robot);
int markerCount(Robot *robot);