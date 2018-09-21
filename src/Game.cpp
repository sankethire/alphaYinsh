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
    Operation* rowStart = NULL;
    Operation* rowEnd = NULL;
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
        if ((tempPoint.color == static_cast<Point::colorType>(playerChance)) 
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

    for (i=ringX+directionX, j=ringY+directionY; 
    (-board.boardSize<=i) && (i<=board.boardSize) &&
    (-board.boardSize<=j) && (j<=board.boardSize); i+=directionX, j+=directionY) {
        Point tempPoint = board.getPointTriLinear(i, j);
        if (tempPoint.piece == Point::marker) {
            seenAnyMarker = true;
        } else if (tempPoint.piece == Point::emptyPiece) {
            std::vector<Operation> tempOpSequence;
            tempOpSequence.push_back(selectRing);
            tempOpSequence.push_back(Operation(Operation::M, i, j));
            moveVectorReturn.push_back(tempOpSequence);
            if (seenAnyMarker) {
                break;
            }
        } else if ((tempPoint.piece == Point::nonExistentPiece) || 
        (tempPoint.piece == Point::ring)) {
            break;
        } 
    }
    return moveVectorReturn;
}

std::vector<std::vector<Move>> Game::possibleMovementForRingAllDirection(Point& ring) {
    std::vector<std::vector<Move>> vecToReturn;
    for (int i=0; i<6; i++) {
        vecToReturn.push_back(possibleMovementForRingInDirection(ring, triLinearDirection[i]));
    }
    return vecToReturn;
}

std::vector<std::vector<std::vector<Move>>> Game::possibleMovementAllRingAllDirection (
    Player& currentPlayer) {
    std::vector<std::vector<std::vector<Move>>> vecToReturn;
    for (Point& ring: currentPlayer.ringLeft) {
        vecToReturn.push_back(possibleMovementForRingAllDirection(ring));
    }
    return vecToReturn;

}

std::tuple<double, double> Game::calculateScore() {
    double scoreA, scoreB;
    std::tuple<double,double> scoreTuple;
    int ringsA = std::get<0>(playerTuple)->ringWon;
    int ringsB = std::get<1>(playerTuple)->ringWon;
    int markersA = std::get<0>(playerTuple)->markerOwn;
    int markersB = std::get<1>(playerTuple)->markerOwn;

    if(ringsA == 3){
        scoreA = 10 - ringsB;
        scoreB = ringsB;
    }
    else if(ringsB == 3){
        scoreA = ringsA;
        scoreB = 10 - ringsA;
    }
    else if(ringsB == ringsA){
        scoreA = 5;
        scoreB = 5;
    }
    else if((ringsA - ringsB) == 2){
        scoreA = 7;
        scoreB = 3;
    }
    else if((ringsB - ringsA) == 2){
        scoreA = 3;
        scoreB = 7;
    }
    else if(ringsA > ringsB){
        scoreA = 6;
        scoreB = 4;
    }
    else if(ringsB > ringsA){
        scoreA = 4;
        scoreB = 6;
    }
    
    scoreA = scoreA + double(markersA)/ 1000.0;
    scoreB = scoreB + double(markersB)/ 1000.0;
    
    
    scoreTuple = std::make_tuple(scoreA, scoreB);

    return scoreTuple;

}

void Game::executeMove(Move fullMove) {
    bool doneSM = false;
    for (int i=0; i<fullMove.operationSequence.size(); i++) {
        Operation& tempOp = fullMove.operationSequence[i];

        // P
        if (tempOp.opcode == Operation::P) {
            if (phase != Game::placement) {
                throw std::invalid_argument
                ("Game must be in placement phase to place rings");
            }

            if (fullMove.operationSequence.size() != 1) {
                throw std::invalid_argument
                ("Only one P and no other move or submove can be done during placement phase");
            }

            executeP(fullMove.operationSequence[0]);
        }

        // S M
        if (tempOp.opcode == Operation::S) {
            if (doneSM) {
                throw std::invalid_argument
                ("Each chance can have only one SM");
            }

            if (phase != Game::movement) {
                throw std::invalid_argument
                ("Game must be in movement phase to move rings");
            }

            if (fullMove.operationSequence.size()-1 < i+1) {
                throw std::invalid_argument
                ("move must have M opcode after S opcode. Move too short");
            }

            Operation& tempOpM = fullMove.operationSequence[i+1];
            if (tempOpM.opcode != Operation::M) {
                throw std::invalid_argument
                ("move must have M opcode after S opcode. Something else after S");
            }

            std::vector<Operation> subMove (fullMove.operationSequence.begin()+i, 
            fullMove.operationSequence.begin()+i+2);
            executeSM(Move(subMove));
            doneSM = true;
            i += 1;
        }

        // RS RE X
        if (tempOp.opcode == Operation::RS) {

            if (phase != Game::movement) {
                throw std::invalid_argument
                ("Game must be in movement phase to remove rings and markers");
            }

            if (fullMove.operationSequence.size()-1 < i+2) {
                throw std::invalid_argument
                ("remove must have RE and X opcode after RS opcode. Move too short");
            }

            if (fullMove.operationSequence[i+1].opcode != Operation::RE) {
                throw std::invalid_argument
                ("remove must have RE opcode after RS opcode. Something else after RS");
                if (fullMove.operationSequence[i+2].opcode != Operation::X) {
                    throw std::invalid_argument
                    ("remove must have X opcode after RE opcode. Something else after RE");
                }
            }

            std::vector<Operation> subMove (fullMove.operationSequence.begin()+i, 
            fullMove.operationSequence.begin()+i+3);
            executeRSREX(Move(subMove));

            i += 2;
        }
    }
}

void Game::executeP(Operation placeOp) {
    Point& gotPoint = board.getPointTriLinear(placeOp.coordinate);
    if (gotPoint.piece != Point::emptyPiece) {
        throw std::invalid_argument
        ("Can only place on points that are empty and exist");
    }
    gotPoint.color = static_cast<Point::colorType>(chance);
    gotPoint.piece = Point::ring;
    int whichPlayer = static_cast<int>(chance);
    if (whichPlayer == 1) {
        std::get<1>(playerTuple)->addRing(gotPoint);
    } else {
        std::get<0>(playerTuple)->addRing(gotPoint);
    }
}

void Game::executeSM(Move SMMove) {
    std::tuple<int,int> mCoord = SMMove.operationSequence[1].coordinate;
    std::tuple<int,int> sCoord = SMMove.operationSequence[0].coordinate;
    std::tuple<int,int> direction = Point::getTriLinearDirection(
    mCoord, sCoord);

    int mCoordX = std::get<0>(mCoord);
    int mCoordY = std::get<1>(mCoord);
    int sCoordX = std::get<0>(sCoord);
    int sCoordY = std::get<1>(sCoord);
    int directionX = std::get<0>(direction);
    int directionY = std::get<1>(direction);

    Point& mPoint = board.getPointTriLinear(mCoord);
    Point& sPoint = board.getPointTriLinear(sCoord);

    Point::colorType colorChance = static_cast<Point::colorType>(chance);

    int i, j;
    bool seenAnyMarker = false;
    for (i=sCoordX+directionX, j=sCoordY+directionY; 
    Point::checkInBetween(i, j, std::make_tuple(sCoordX+directionX, sCoordY+directionY), 
    std::make_tuple(mCoordX-directionX, mCoordY-directionY)); i+=directionX, j+=directionY) {
        Point& tempPoint = board.getPointTriLinear(i, j);
        if (tempPoint.piece == Point::marker) {
            tempPoint.flip();
            seenAnyMarker = true;
        } else if (tempPoint.piece == Point::emptyPiece) {
            if (seenAnyMarker) {
                throw std::invalid_argument("Ring jumped over markers then a empty");
            }
        } else {
            throw std::invalid_argument("During marker movement S -> M just passed over ring or nonExistent.");
        }
    }

    if (sPoint.piece == Point::ring) {
        if (sPoint.color == colorChance) {
            sPoint.piece = Point::marker;
        } else {
            throw std::invalid_argument("cooridinate of point S is not same color");
        }
    } else {
        throw std::invalid_argument("cooridinate of point S is not ring");
    }

    if (mPoint.piece == Point::emptyPiece) {
        mPoint.piece = Point::ring;
        mPoint.color = colorChance;
    } else {
        throw std::invalid_argument("cooridinate of point M are not empty");
    }


    int whichPlayer = static_cast<int>(chance);
    if (whichPlayer == 1) {
        std::get<1>(playerTuple)->removeRing(sPoint);
        std::get<1>(playerTuple)->addRing(mPoint);
    } else {
        std::get<0>(playerTuple)->removeRing(sPoint);
        std::get<0>(playerTuple)->addRing(mPoint);
    }
}

void Game::executeRSREX(Move RSREXMove) {
    std::tuple<int,int> reCoord = RSREXMove.operationSequence[1].coordinate;
    std::tuple<int,int> rsCoord = RSREXMove.operationSequence[0].coordinate;
    std::tuple<int,int> direction = Point::getTriLinearDirection(
    reCoord, rsCoord);

    int reCoordX = std::get<0>(reCoord);
    int reCoordY = std::get<1>(reCoord);
    int rsCoordX = std::get<0>(rsCoord);
    int rsCoordY = std::get<1>(rsCoord);
    int directionX = std::get<0>(direction);
    int directionY = std::get<1>(direction);

    Point& rePoint = board.getPointTriLinear(reCoord);
    Point& rsPoint = board.getPointTriLinear(rsCoord);
    Point::colorType colorChance = static_cast<Point::colorType>(chance);

    int i, j;
    for (i=rsCoordX, j=rsCoordY; 
    Point::checkInBetween(i, j, rsCoord, reCoord); i+=directionX, j+=directionY) {
        Point& tempPoint = board.getPointTriLinear(i, j);

        if (tempPoint.piece == Point::marker) {
            if (tempPoint.color == colorChance) {
                tempPoint.piece = Point::emptyPiece;
                tempPoint.color = Point::emptyColor;
            } else {
                throw std::invalid_argument
                ("Cannot remove others markers. Or some piece are messed up. marker non chance color");
            }
        } else {
            throw std::invalid_argument
            ("Non marker piece found in between RS and RE points");
        }
    }

    std::tuple<int,int> xCoord = RSREXMove.operationSequence[2].coordinate;
    Point& xPoint = board.getPointTriLinear(xCoord);

    if (xPoint.piece != Point::ring) {
        throw std::invalid_argument
        ("Can only remove ring piece");
    }

    if (xPoint.color != colorChance) {
        throw std::invalid_argument
        ("Can only remove ring of your own color.");
    }

    xPoint.piece = Point::emptyPiece;
    xPoint.color = Point::emptyColor;

    int whichPlayer = static_cast<int>(chance);
    if (whichPlayer == 1) {
        std::get<1>(playerTuple)->removeRing(xPoint);
        std::get<1>(playerTuple)->ringWon += 1;
    } else {
        std::get<0>(playerTuple)->removeRing(xPoint);
        std::get<0>(playerTuple)->ringWon += 1;
    }
}