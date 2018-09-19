#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Point.h"
#include "Move.h"
#include "Operation.h"


#include <vector>
#include <tuple>

Game::Game(int ringAtStart) {
    phase = placement;
    chance = orange;
    ringNum = ringAtStart;
    board = Board(ringAtStart);
    Player* p1 = new Player(board);
    Player* p2 = new Player(board);
    playerTuple = std::make_tuple(p1, p2);
}

std::vector<Move> Game::contiguousMarker(int contiguousNum, chanceType playerChance) {
    // loop constraint variables
    std::vector<Move> movesToReturn;
    int jMin;
    int jMax;
    int iMin;
    int iMax;
    bool seenSameColorMarker;
    int numOfContiguous;
    Operation* rowStart;
    Operation* rowEnd;
    std::vector<Operation*> tempOpQueue;

    auto convertToNormalVector = [&] (std::vector<Operation*> opPtrVector) {
        std::vector<Operation> opVector;
        for (int i=0; i<opPtrVector.size(); i++) {
            opVector.push_back(*(opPtrVector[i]));
        }
        return opVector;
    };

    // lambda function for repitive code.
    auto checkAndAddContigous = [&] (int directionX, int directionY, int i, int j) {
        Point tempPoint = board.getPointTriLinear(i, j);

        // seen same color marker 
        if ((static_cast<int>(tempPoint.color) == static_cast<int>(playerChance)) 
        && (tempPoint.piece == Point::marker)) {
            if (!seenSameColorMarker) {
                tempOpQueue.clear();
                rowStart =  new Operation(Operation::RS, i, j);
                seenSameColorMarker = true;
            }
            numOfContiguous++;
            if (numOfContiguous >= contiguousNum) {
                rowEnd = new Operation(Operation::RE, i, j);
                tempOpQueue.push_back(rowStart);
                tempOpQueue.push_back(rowEnd);
                Move tempMoveStore = Move(convertToNormalVector(tempOpQueue));
                movesToReturn.push_back(tempMoveStore);
                tempOpQueue.clear();
                int tempCoordX = std::get<0>(rowStart->coordinate);
                int tempCoordY = std::get<1>(rowStart->coordinate);
                rowStart =  new Operation(Operation::RS, tempCoordX+directionX, tempCoordY+directionY);
            }
        } else {
            numOfContiguous = 0;
            seenSameColorMarker = false;
        }
    };

    // +(0, 1) direction
    for (int i=-board.boardSize; i<=board.boardSize; i++) {
        tempOpQueue.clear();
        numOfContiguous = 0;
        seenSameColorMarker = false;

        // see only majority of existent
        if (i<=0) {
            jMax = i+board.boardSize;
            jMin = -board.boardSize;
        } else {
            jMin = i-board.boardSize;
            jMax = board.boardSize;
        }
        for (int j=jMin; j<=jMax; j++) {
            checkAndAddContigous(0, 1, i, j);
        }
    }

    // +(1, 0) direction
    for (int j=-board.boardSize; j<=board.boardSize; j++) {
        tempOpQueue.clear();
        numOfContiguous = 0;
        seenSameColorMarker = false;
        if (j<=0) {
            iMax = j+board.boardSize;
            iMin = -board.boardSize;
        } else {
            iMin = j-board.boardSize;
            iMax = board.boardSize;
        }
        for (int i=iMin; i<=iMax; i++) {
            checkAndAddContigous(1, 0, i, j);
        }
    }

    // +(1, 1) direction
    int i;
    int j;
    // y = -boardSize starting points
    for (iMin = -board.boardSize; iMin <= 0; iMin++) {
        tempOpQueue.clear();
        numOfContiguous = 0;
        seenSameColorMarker = false;
        for (i = iMin, j = -board.boardSize; (i <= board.boardSize) && (j <= board.boardSize); i++, j++) {
            checkAndAddContigous(1, 1, i, j);
        }
    }

    // x = -boardSize starting points
    for (jMin = -board.boardSize+1; jMin <= 0; jMin++) {
        tempOpQueue.clear();
        numOfContiguous = 0;
        seenSameColorMarker = false;
        for (i = -board.boardSize, j = jMin; (i <= board.boardSize) && (j <= board.boardSize); i++, j++) {
            checkAndAddContigous(1, 1, i, j);
        }
    }
    delete rowStart;
    delete rowEnd;
    return movesToReturn;
}

std::vector<Move> Game::possibleMovementForRingInDirection
(Point& ring, std::tuple<int, int> direction) {
    int directionX = std::get<0>(direction);
    int directionY = std::get<1>(direction);
    int ringX = std::get<0>(ring.triLinearCoord);
    int ringY = std::get<1>(ring.triLinearCoord);
    int i, j;
    bool seenAnyMarker = false;
    Operation selectRing = Operation(Operation::S, ringX, ringY);
    std::vector<Move> moveVectorReturn;

    for (i=ringX, j=ringY; (-board.boardSize<=i) && (i<=board.boardSize) &&
    (-board.boardSize<=j) && (j<=board.boardSize); i+=directionX, j+=directionY) {
        Point tempPoint = board.getPointTriLinear(i, j);
        if (tempPoint.piece == Point::marker) {
            seenAnyMarker = true;
        } else if (tempPoint.piece == Point::emptyPiece) {
            // FIXME: care here initialize new vector.
            std::vector<Operation> tempOpSequence;
            tempOpSequence.push_back(selectRing);
            tempOpSequence.push_back(Operation(Operation::M, i, j));
            moveVectorReturn.push_back(tempOpSequence);
            if (seenAnyMarker) {
                break;
            }
        } else if (tempPoint.piece == Point::nonExistentPiece) {
            break;
        } 
    }
}

std::vector<std::vector<Move>> Game::possibleMovementForRingAllDirection(Point ring) {
    std::vector<std::vector<Move>> vecToReturn;
    for (std::tuple<int, int>& directionTup: triLinearDirection) {
        vecToReturn.push_back(possibleMovementForRingInDirection(ring, directionTup));
    }
    return vecToReturn;
}

std::vector<std::vector<std::vector<Move>>> Game::possibleMovementAllRingAllDirection (
    Player currentPlayer) {
    std::vector<std::vector<std::vector<Move>>> vecToReturn;
    for (Point& ring: currentPlayer.ringLeft) {
        vecToReturn.push_back(possibleMovementForRingAllDirection(ring));
    }
    return vecToReturn;

}
