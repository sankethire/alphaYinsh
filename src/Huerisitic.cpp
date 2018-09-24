#include "Huerisitic.h"
#include "Node.h"
#include "Game.h"
#include "Board.h"
#include "Move.h"
#include "Point.h"

#include <tuple>
#include <vector>
#include <cmath>

int Huerisitic::markerDiff(Game& g) {
    Player* chancePlayer;
    Player* otherPlayer;
    if (g.chance == Game::orange) {
        chancePlayer = &(std::get<0>(g.playerTuple));
        otherPlayer = &(std::get<1>(g.playerTuple));
    } else {
        chancePlayer = &(std::get<1>(g.playerTuple));
        otherPlayer = &(std::get<0>(g.playerTuple));
    }
    return ((chancePlayer->markerOwn)-(otherPlayer->markerOwn));
}

bool Huerisitic::markerDiffComparator(std::tuple<Move, Node*> tup1, 
std::tuple<Move, Node*> tup2) {
    Node* n1 = std::get<1>(tup1);
    Node* n2 = std::get<1>(tup2);
    return (markerDiff(n1->gameState) < markerDiff(n2->gameState));
}

double Huerisitic::centeringRingScore(Point& toCalculateOnRing, int gameBoardSize) {
    double weightExpIncCloserToCenter = 3;
    std::tuple<int, int>  hexCoordinates = 
    Point::conversionToHexCoord(toCalculateOnRing.triLinearCoord);
    int hexagonNum = std::get<0>(hexCoordinates);
    return pow(weightExpIncCloserToCenter, gameBoardSize-hexagonNum+1);
}

double Huerisitic::mobilityAllRingScore(Game& toCalculateOnGame) {
    int movementOrange = toCalculateOnGame.possibleMovementOfRings(Game::orange).size();
    int movementBlue = toCalculateOnGame.possibleMovementOfRings(Game::blue).size();
    if (toCalculateOnGame.chance == Game::orange) {
        return static_cast<double>(movementOrange-movementBlue);
    }
    return static_cast<double>(movementBlue-movementOrange);
}

double Huerisitic::centeringAllRingScore(Game& toCalculateOnGame) {
    double centeringOrange = 0;
    double centeringBlue = 0;
    for (Point& eachRing: 
    toCalculateOnGame.getPlayerFromColor(Game::orange).ringLeft) {
        centeringOrange += centeringRingScore(eachRing, toCalculateOnGame.sizeOfBoard);
    }
    for (Point& eachRing: 
    toCalculateOnGame.getPlayerFromColor(Game::blue).ringLeft) {
        centeringBlue += centeringRingScore(eachRing, toCalculateOnGame.sizeOfBoard);
    }
    if (toCalculateOnGame.chance == Game::orange) {
        return centeringOrange-centeringBlue;
    }
    return centeringBlue-centeringOrange;
}

double Huerisitic::combinedUtility(Game& toCalculateOnGame) {
    if (toCalculateOnGame.phase == Game::placement) {
        double weigthRingMobility = 1;
        double weigthRingCentering = 100;

        double mobilityRingsScoreReturned = mobilityAllRingScore(toCalculateOnGame);
        double centeringRingScoreReturned = centeringAllRingScore(toCalculateOnGame);

        return weigthRingMobility*mobilityRingsScoreReturned + 
        weigthRingCentering*centeringRingScoreReturned;

    } else {
        double weigthRingMobility = 1;
        double weigthRingCentering = 0.01;
        double weightContinuousMarker = 1;
        double weightFlipped = 1;

        double weightSuccessiveMarker = 3;
        double weightExpIncPerIncMarkerTillLimit = 4;

        double mobilityRingsScoreReturned = mobilityAllRingScore(toCalculateOnGame);
        double centeringRingScoreReturned = centeringAllRingScore(toCalculateOnGame);
        double continousMarkerScoreReturned;
        double flippedScoreReturned;

        double continuousMarkerScoreOrange = 0;
        double flippedScoreOrange = 0;
        double continuousMarkerScoreBlue = 0;
        double flippedScoreBlue = 0;

        int ringInRowOrange;
        int ringInRowBlue;
        int markerInRowOrange;
        int markerInRowBlue;

        auto resetNumInRow = [&] () {
            ringInRowOrange = 0;
            ringInRowBlue = 0;
            markerInRowOrange = 0;
            markerInRowBlue = 0;
        };

        auto updateNumInRow = [&] (int i, int j) {
            Point& gotP = toCalculateOnGame.board.getPointTriLinear(i, j);

            if (gotP.piece == Point::ring) {
                if (gotP.color == Point::orange) {
                    ringInRowOrange++;
                } else if (gotP.color == Point::blue) {
                    ringInRowBlue++;
                }
            } else if (gotP.piece == Point::marker) {
                if (gotP.color == Point::orange) {
                    markerInRowOrange++;
                } else if (gotP.color == Point::blue) {
                    markerInRowBlue++;
                }
            }
            
            if (markerInRowBlue < toCalculateOnGame.sizeOfBoard) {
                continuousMarkerScoreOrange += 
                std::pow(weightExpIncPerIncMarkerTillLimit, markerInRowBlue);
            }
            if (markerInRowOrange < toCalculateOnGame.sizeOfBoard) {
                continuousMarkerScoreOrange += 
                std::pow(weightExpIncPerIncMarkerTillLimit, markerInRowOrange);
            }
        };

        auto checkFlipping = [&] () {
            if ((ringInRowOrange >= 1) && (ringInRowBlue == 0)) {
                flippedScoreOrange += (markerInRowBlue-markerInRowOrange);
            } else if ((ringInRowBlue >= 1) && (ringInRowOrange == 0)) {
                flippedScoreBlue += (markerInRowOrange-markerInRowBlue);
            }
        };

        int jMin;
        int jMax;
        int iMin;
        int iMax;
        // effiecient iterating in directions
        for (int i=-toCalculateOnGame.sizeOfBoard; i<=toCalculateOnGame.sizeOfBoard; i++) {
            resetNumInRow();
            
            if (i<=0) {
                jMax = i+toCalculateOnGame.sizeOfBoard;
                jMin = -toCalculateOnGame.sizeOfBoard;
            } else {
                jMin = i-toCalculateOnGame.sizeOfBoard;
                jMax = toCalculateOnGame.sizeOfBoard;
            }
            for (int j=jMin; j<=jMax; j++) {
                // TODO: iterating here
                updateNumInRow(i, j);

            }
            checkFlipping();
        }

        // +(1, 0) direction
        for (int j=-toCalculateOnGame.sizeOfBoard; j<=toCalculateOnGame.sizeOfBoard; j++) {
            resetNumInRow();

            if (j<=0) {
                iMax = j+toCalculateOnGame.sizeOfBoard;
                iMin = -toCalculateOnGame.sizeOfBoard;
            } else {
                iMin = j-toCalculateOnGame.sizeOfBoard;
                iMax = toCalculateOnGame.sizeOfBoard;
            }
            for (int i=iMin; i<=iMax; i++) {
                // TODO: iterating here
                updateNumInRow(i, j);
            }
            checkFlipping();
        }

        // +(1, 1) direction
        int i;
        int j;
        // y = -boardSize starting points
        for (iMin = -toCalculateOnGame.sizeOfBoard; iMin <= 0; iMin++) {
            resetNumInRow();

            for (i = iMin, j = -toCalculateOnGame.sizeOfBoard; 
            (i <= toCalculateOnGame.sizeOfBoard) && (j <= toCalculateOnGame.sizeOfBoard); 
            i++, j++) {
                // TODO: iterating here
                updateNumInRow(i, j);
            }
            checkFlipping();
        }

        // x = -boardSize starting points
        for (jMin = -toCalculateOnGame.sizeOfBoard+1; jMin <= 0; jMin++) {
            resetNumInRow();

            for (i = -toCalculateOnGame.sizeOfBoard, j = jMin; 
            (i <= toCalculateOnGame.sizeOfBoard) && (j <= toCalculateOnGame.sizeOfBoard); 
            i++, j++) {
                // TODO: iterating here
                updateNumInRow(i, j);
            }
            checkFlipping();
        }

        // calculate for orange
        continousMarkerScoreReturned = 
        continuousMarkerScoreOrange - continuousMarkerScoreBlue;
        flippedScoreReturned = flippedScoreOrange - flippedScoreBlue;
        if (toCalculateOnGame.chance == Game::blue) {
            // reverse sign if blue
            continousMarkerScoreReturned = -continousMarkerScoreReturned;
            flippedScoreReturned = -flippedScoreReturned;
        }

        double combinedScore = 
        weigthRingMobility*mobilityRingsScoreReturned +
        weigthRingCentering*centeringRingScoreReturned +
        weightContinuousMarker*continousMarkerScoreReturned +
        weightFlipped*flippedScoreReturned;

        double currentPlayerScore;

        if (toCalculateOnGame.chance == Game::orange) {
            currentPlayerScore = std::get<0>(toCalculateOnGame.calculateScore());
        } else {
            currentPlayerScore = std::get<1>(toCalculateOnGame.calculateScore());
        }

        // FIXME: try this ai doesn't finish rings first
        // combinedScore = combinedScore*(currentPlayerScore)*0.5;
        
        return combinedScore;
    }
}
