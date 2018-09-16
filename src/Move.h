#ifndef MOVE_H
#define MOVE_H

#include "Point.h"
#include "Operation.h"

#include <string>
#include <vector>
#include <tuple>

class Move {
public:
    /* FIELDS */

    

    /* FUNCTIONS */

    // constructor converts string of form of 
    // hexCoord to Move object(which stores in form of TriLinearCoord)
    Move(std::string sFromTerminal);
};

#endif /* MOVE_H */