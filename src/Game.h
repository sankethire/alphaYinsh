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

    std::vector<Move> possibleMovesForRingInDirection(Point ring, std::tuple<int, int> direction);
    // Moves() parses HexCoord in string format and gives it to this function
    std::vector<Move> possibleMovesForRingAllDirection(Point ring);
    // find all possible moves for rings of current player
    std::vector<std::vector<Move>> possibleMovesAllRingAllDirection(Player currentPlayer);

    // changes board configuration according to move(if valid)
    void ExecuteMove(Move m);
    std::tuple<int, int> calculateScore();

    // checks validity of move before it is execute.
    // searchs moves in currentPlayerPossibleMovesAllRings array
    bool checkMoveValidity(Move m);
};

#endif /* GAME_H */