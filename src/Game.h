#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "Move.h"

#include <vector>
#include <tuple>

class Game {
public:
    /* FIELDS */

    // Board DS
    Board board;
    // Number of rings each player has at start of game. Board coordinate range = (-ringNum, ringNum)
    int ringNum;

    // players in game. 0 moves first.
    std::tuple<Player, Player> playerTuple;

    // possibles moves for player which has current chance
    std::vector<std::vector<Move>> currentPlayerPossibleMovesAllRings;

    /* FUNCTIONS */
    Game();

    // Moves() parses HexCoord in string format and gives it to this function
    std::vector<Move> possibleMovesForRing(Point ring);
    
    // changes board configuration to
    void ExecuteMove(Move m);
    std::vector<int> calculateScore();

    // checks validity of move before it is execute.
    // searchs move 
    bool checkMoveValidity(Move m);
};

#endif /* GAME_H */