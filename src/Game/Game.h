#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "Move.h"

#include <vector>
#include <tuple>
#include <memory>

class Game {
public:
    /* FIELDS */

    // Board DS
    std::shared_ptr<Board> board;
    // Number of rings each player has at start of game. 
    // Game settings

    // Generally Board coordinate range = (-ringNum, ringNum)
    int sizeOfBoard;
    // initially 2*ringsToBePlacedPerPlayer moves are done then movement phase starts.
    int ringsToBePlacedPerPlayer;
    // number of rings to be removed to win the game.
    int ringsToWin;
    // number of marker that are legal to remove in one move.
    int numberOfMarkersToRemove;
    // moves left till end of placement phase
    int movesLeftTillPlacementEnd;

    // Game phase: Placement, Movement
    enum phaseType {placement, movement};
    phaseType phase;

    enum chanceType {orange, blue};
    chanceType chance;

    // players in game. 0 moves first.
    std::tuple<std::shared_ptr<Player>, std::shared_ptr<Player>> playerTuple;

    // // possibles moves for player which has current chance
    // std::vector<std::vector<Move>> currentPlayerPossibleMovesAllRings;

    /* FUNCTIONS */
    Game();
    Game(int sizeOfBoardInput, int ringsToBePlacedPerPlayerInput, 
    int ringsToWinInput, int numberOfMarkersToRemoveInput);

    // deep copy
    std::shared_ptr<Game> clone();

    // changes board configuration according to move(if valid)
    void executeMove(Move fullMove);

    // Sub parts of execute move
    void executeP(Operation placeOp);
    void executeSM(Move SMMove);
    void executeRSREX(Move RSREXMove);

    // Helpers
    void chanceFlip();
    std::shared_ptr<Player> getPlayerFromColor(chanceType playerChance);
    bool hasSomeoneWon();

    // Play game
    void play();

    // default score constructor.
    std::tuple<double, double> calculateScore();

    // // checks validity of move before it is execute.
    // // searchs moves in currentPlayerPossibleMovesAllRings array
    // bool checkMoveValidity(Move m);

    // Possible SubMoves
    // Possible P
    std::vector<Move> possiblePlacement();

    // Possible S M
    std::vector<Move> possibleMovementForRingInDirection(
    Point& ring, std::tuple<int, int> direction);
    // Moves() parses HexCoord in string format and gives it to this function
    std::vector<std::vector<Move>> possibleMovementForRingAllDirection(Point& ring);
    // find all possible moves for rings of current player
    std::vector<std::vector<std::vector<Move>>> possibleMovementAllRingAllDirection(
    chanceType playerChance);
    // flatten the vector of vectors of ... 
    std::vector<Move> possibleMovementOfRings(chanceType playerChance);

    // Possible RS RE
    // find contigous (contiguousNum) # of markers in each linear direction.
    // return something like RS (0, -2) RE (4, 2).
    // note this doesn't give the X part.
    std::vector<Move> contiguousMarker(int contiguousNum, chanceType playerChance);

    // Possible X
    std::vector<Move> possibleRingRemoval(chanceType playerChance);
};

#endif /* GAME_H */