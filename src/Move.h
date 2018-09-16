#ifndef MOVE_H
#define MOVE_H

#include <Point.h>

#include <string>
#include <vector>
#include <tuple>

class Move {
public:
    /* FIELDS */

    // type of moves in game
    enum moveType {P, SM, RSREX};
    moveType move;

    // According to move type, list of 3 tuple(coordinate) of point. 
    // ex: S convertToThreeCoord(1, 2) M convertToThreeCoord(2, 4)
    std::vector<std::tuple<int, int, int>> pointInMove;

    /* FUNCTIONS */

    // constructor converts string of form of 
    // hexCoord to Move object(which stores in form of TriLinearCoord)
    Move(std::string sFromTerminal);
};

#endif /* MOVE_H */