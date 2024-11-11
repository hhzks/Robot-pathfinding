This is an implementation of Stage 7

- The program generates a random seed based on the time
- The program generates a randomly shaped and sized grid, with the home tile as close as possible to the centre. 
- Up to 20 obstacles and up to 10 markers are generated
- The robot starts from a random point in the arena, and uses a depth-first search algorithm to search the arena for markers as well as locate the home tile
- Once the robot has collected all the markers, it will return to the home tile

To compile:
- gcc main.c graphics.c map.c robot.c pathfinding.c animation.c
or
- clang main.c graphics.c map.c robot.c pathfinding.c animation.c
