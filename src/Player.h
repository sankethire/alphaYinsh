#ifndef PLAYER_H
#define PLAYER_H

#include "Point.h"
#include "Board.h"

#include <vector>

class Player {
public:
    /* FIELDS */

    // rings won by player. Cannot reduce
    int ringWon;
    // list of points of rings left for player. Used for possible moves
    std::vector<Point> ringLeft;
    // markers owned by player. Can decrease or increase
    int markerOwn;

    // Playing Board
    Board playingBoard;

    /* FUNCTIONS */

    // TODO: = 5 default.
    Player(Board playBoard = 5);

    // add ring which was placed in placement phase to ringLeft Vector.
    void addRing(Point ringToAdd);
    void addRing(int ringToRemoveX, int ringToRemoveY);

    // remove ring from list of ring left and increment ringWon.
    void removeRing(Point ringToRemove);
    void removeRing(int ringToRemoveX, int ringToRemoveY);
};

#endif /* PLAYER_H */