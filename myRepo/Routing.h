#ifndef Routing_h
#define Routing_h
#include "farmpoint.h"
#include <stack>

//EFFECTS: returns 1 if the farmpoint can be moved to
//         returns 0 if the farmpoint cant be moved to
//         returns 2 if the farmpoint is the start
char check_valid_q(char** map, Farmpoint pt, int farmsize);

//EFFECTS: returns 1 if the farmpoint can be moved to
//         returns 0 if the farmpoint cant be moved to
//         returns 2 if the farmpoint is the Big Buck
char check_valid_s(char** map, Farmpoint pt, int farmsize, int farmcount);

//REQUIRES: map points to a 2D array with dimensions farmsize*farmcount by
//          farmsize
//          start contains the location of the 'S' in map 
//MODIFIES: map
//EFFECTS: Modifies the map to contain the path taken by a stack routing scheme
//         Returns true if buck was found, false otherwise
bool stackRout(char** map, int farmsize, int farmcount, Farmpoint start);

//REQUIRES: current points to a deadend farmpoint
//MODIFIES: map
//EFFECTS: backtracks from current until a farmpoint with a possible move
//         is found
void backtrack(char** map, Farmpoint current, int farmsize,
               Farmpoint top, int farmcount);

bool pt_exists(Farmpoint pt, int farmsize, int farmcount);

//REQUIRES: map points to a 2D array with dimensions farmsize*farmcount by
//          farmsize
//          start contains the location of the 'S' in map
//MODIFIES: map
//EFFECTS: Modifies the map to contain the path taken by a queue routing scheme
//         Returns true if buck was found, false otherwise
bool queueRout(char** map, int farmsize, int farmcount, Farmpoint start);

//REQUIRES: mapcopy contains the original map
//MODIFIES: map
//EFFECTS: Modifies a map created by a queueRouting to only contain the
//         path taken
void dequeueMap(char** map, char** mapcopy, Farmpoint buck, 
                Farmpoint start, int farmsize, int farmcount);

#endif
