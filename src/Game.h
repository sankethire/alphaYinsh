#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "Move.h"

#include <vector>

class Game {
    /* FIELDS */

    // Board DS
    Board board;
    // Number of rings each player has at start of game. Board coordinate range = (-ringNum, ringNum)
    int ringNum;

    // players in game. 0 moves first.
    Player playerArray [2];

    /* FUNCTIONS */
    Game();
    std::vector<Move> possibleMovesForRing(Point ring);
    void ExecuteMove(Move m);
    std::vector<int> calculateScore();
    bool checkMoveValidity(Move m);
};

#endif /* GAME_H */