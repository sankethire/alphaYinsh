#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

class Player {
    /* FIELDS */

    // rings won by player. Cannot reduce
    int ringWon;
    // list of points of rings left for player. Used for possible moves
    std::vector<Point> ringLeft;
    // markers owned by player. Can decrease or increase
    int markerOwn;

    /* FUNCTIONS */

    Player();
    // remove ring from list of ring left and increment ringWon
    void removeRing(Point ringToRemove);
};

#endif /* PLAYER_H */