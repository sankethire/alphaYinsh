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
    // Number of rings each player has at start of game. 
    // Generally Board coordinate range = (-ringNum, ringNum)
    // Game settings
    int sizeOfBoard;
    int ringsToBePlacedPerPlayer;
    int ringsToWin;
    int numberOfMarkersToRemove;
    
    // Game phase: Placement, Movement
    enum phaseType {placement, movement};
    phaseType phase;

    enum chanceType {orange, blue};
    chanceType chance;

    // players in game. 0 moves first.
    std::tuple<Player*, Player*> playerTuple;

    // possibles moves for player which has current chance
    std::vector<std::vector<Move>> currentPlayerPossibleMovesAllRings;

    /* FUNCTIONS */
    Game(int sizeOfBoardInput, int ringsToBePlacedPerPlayerInput, 
    int ringsToWinInput, int numberOfMarkersToRemoveInput);

    std::vector<Move> possibleMovementForRingInDirection
    (Point& ring, std::tuple<int, int> direction);
    // Moves() parses HexCoord in string format and gives it to this function
    std::vector<std::vector<Move>> possibleMovementForRingAllDirection(Point& ring);
    // find all possible moves for rings of current player
    std::vector<std::vector<std::vector<Move>>> possibleMovementAllRingAllDirection
    (Player& currentPlayer);

    // changes board configuration according to move(if valid)
    void executeMove(Move fullMove);

    // Sub parts of execute move
    void executeP(Operation placeOp);
    void executeSM(Move SMMove);
    void executeRSREX(Move RSREXMove);

    // Play game
    void play();

    // default score constructor.
    std::tuple<double, double> calculateScore();

    // checks validity of move before it is execute.
    // searchs moves in currentPlayerPossibleMovesAllRings array
    bool checkMoveValidity(Move m);

    // find contigous (contiguousNum) # of markers in each linear direction.
    // return something like RS (0, -2) RE (4, 2).
    // note this doesn't give the X part.
    std::vector<Move> contiguousMarker(int contiguousNum, chanceType playerChance);
};

#endif /* GAME_H */