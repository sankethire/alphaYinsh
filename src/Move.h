#ifndef MOVE_H
#define MOVE_H

#include <string>

class Move {
    /* FIELDS */

    // type of moves in game
    enum moveType {P, SM, SM_RSREX, RSREX_SM};
    moveType move;

    /* FUNCTIONS */
    Move(std::string sFromTerminal);
};

#endif /* MOVE_H */