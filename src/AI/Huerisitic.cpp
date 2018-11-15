#include "Huerisitic.h"
#include "Node.h"
#include "../Game/Game.h"
#include "../Game/Board.h"
#include "../Game/Move.h"
#include "../Game/Point.h"

#include <tuple>
#include <vector>
#include <cmath>
#include <memory>

int Huerisitic::markerDiff(std::shared_ptr<Game> g, Game::chanceType whosUtil) {
    std::shared_ptr<Player> chancePlayer;
    std::shared_ptr<Player> otherPlayer;
    if (whosUtil == Game::orange) {
        chancePlayer = std::get<0>(g->playerTuple);
        otherPlayer = std::get<1>(g->playerTuple);
    } else {
        chancePlayer = std::get<1>(g->playerTuple);
        otherPlayer = std::get<0>(g->playerTuple);
    }
    return ((chancePlayer->markerOwn)-(otherPlayer->markerOwn));
}

bool Huerisitic::markerDiffComparator(std::tuple<Move, std::shared_ptr<Node>> tup1, 
std::tuple<Move, std::shared_ptr<Node>> tup2, Game::chanceType whosUtil) {
    std::shared_ptr<Node> n1 = std::get<1>(tup1);
    std::shared_ptr<Node> n2 = std::get<1>(tup2);
    return (markerDiff(n1->gameState, whosUtil) < markerDiff(n2->gameState, whosUtil));
}

double Huerisitic::centeringRingScore(Point& toCalculateOnRing, int gameBoardSize) {
    double weightExpIncCloserToCenter = 3;
    std::tuple<int, int>  hexCoordinates = 
    Point::conversionToHexCoord(toCalculateOnRing.triLinearCoord);
    int hexagonNum = std::get<0>(hexCoordinates);
    return pow(weightExpIncCloserToCenter, gameBoardSize-hexagonNum+1);
}

double Huerisitic::mobilityAllRingScore(Game& toCalculateOnGame, 
Game::chanceType whosUtil) {
    int movementOrange = toCalculateOnGame.possibleMovementOfRings(Game::orange).size();
    int movementBlue = toCalculateOnGame.possibleMovementOfRings(Game::blue).size();
    if (whosUtil == Game::orange) {
        return static_cast<double>(movementOrange-movementBlue);
    }
    return static_cast<double>(movementBlue-movementOrange);
}

double Huerisitic::centeringAllRingScore(Game& toCalculateOnGame, 
Game::chanceType whosUtil) {
    double centeringOrange = 0;
    double centeringBlue = 0;
    for (Point& eachRing: 
    toCalculateOnGame.getPlayerFromColor(Game::orange)->ringLeft) {
        centeringOrange += centeringRingScore(eachRing, toCalculateOnGame.sizeOfBoard);
    }
    for (Point& eachRing: 
    toCalculateOnGame.getPlayerFromColor(Game::blue)->ringLeft) {
        centeringBlue += centeringRingScore(eachRing, toCalculateOnGame.sizeOfBoard);
    }
    if (whosUtil == Game::orange) {
        return centeringOrange-centeringBlue;
    }
    return centeringBlue-centeringOrange;
}

double Huerisitic::combinedUtility(Game& toCalculateOnGame, Game::chanceType whosUtil) {
    if (toCalculateOnGame.phase == Game::placement) {
        double weigthRingMobility = 1;
        double weigthRingCentering = 100;

        double mobilityRingsScoreReturned = mobilityAllRingScore(toCalculateOnGame, whosUtil);
        double centeringRingScoreReturned = centeringAllRingScore(toCalculateOnGame, whosUtil);

        return weigthRingMobility*mobilityRingsScoreReturned + 
        weigthRingCentering*centeringRingScoreReturned;

    } else {
        double weigthRingMobility = 0.3;
        double weigthRingCentering = 0.2;
        double weightMarkerScore = 10;
        double weightFlipped = 50;
        double weightRingWon = 10000;
        double weightContiguousMarker = 140;

        double weightSuccessiveMarker = 2;
        double successiveRingCollectIncrease = 10;
        double weightSecurity = 10;
        int threshOfmarkerSecurity = toCalculateOnGame.numberOfMarkersToRemove - 1;

        double mobilityRingsScoreReturned = mobilityAllRingScore(toCalculateOnGame, whosUtil);
        double centeringRingScoreReturned = centeringAllRingScore(toCalculateOnGame, whosUtil);
        double markerScoreReturned;
        double flippedScoreReturned;
        double ringWonScoreReturned;
        double contiguousMarkerScoreReturned;
        

        double markerScoreOrange = 0;
        double flippedScoreOrange = 0;
        double markerScoreBlue = 0;
        double flippedScoreBlue = 0;

        int ringInRowOrange;
        int ringInRowBlue;
        int markerInRowOrange;
        int markerInRowBlue;

        int continuousRingInRowOrange;
        int continuousRingInRowBlue;
        int continuousMarkerInRowOrange;
        int continuousMarkerInRowBlue;

        double contiguousMarkerOrange = 
        toCalculateOnGame.contiguousMarker(toCalculateOnGame.numberOfMarkersToRemove - 1, Game::orange).size();
        double contiguousMarkerBlue = 
        toCalculateOnGame.contiguousMarker(toCalculateOnGame.numberOfMarkersToRemove - 1, Game::blue).size();

        auto resetNumInRow = [&] () {
            ringInRowOrange = 0;
            ringInRowBlue = 0;
            markerInRowOrange = 0;
            markerInRowBlue = 0;
            continuousRingInRowOrange = 0;
            continuousRingInRowBlue = 0;
            continuousMarkerInRowOrange = 0;
            continuousMarkerInRowBlue = 0;
        };

        auto updateNumInRow = [&] (int i, int j) {
            Point& gotP = toCalculateOnGame.board->getPointTriLinear(i, j);

            if (gotP.piece == Point::ring) {
                if (gotP.color == Point::orange) {
                    ringInRowOrange++;
                    continuousRingInRowOrange++;
                    continuousRingInRowBlue = 0;
                    continuousMarkerInRowOrange = 0;
                    continuousMarkerInRowBlue = 0;
                } else if (gotP.color == Point::blue) {
                    ringInRowBlue++;
                    continuousRingInRowOrange = 0;
                    continuousRingInRowBlue++;
                    continuousMarkerInRowOrange = 0;
                    continuousMarkerInRowBlue = 0;
                }
            } else if (gotP.piece == Point::marker) {
                if (gotP.color == Point::orange) {
                    markerInRowOrange++;
                    continuousRingInRowOrange = 0;
                    continuousRingInRowBlue = 0;
                    continuousMarkerInRowOrange++;
                    continuousMarkerInRowBlue = 0;
                } else if (gotP.color == Point::blue) {
                    markerInRowBlue++;
                    continuousRingInRowOrange = 0;
                    continuousRingInRowBlue = 0;
                    continuousMarkerInRowOrange = 0;
                    continuousMarkerInRowBlue++;
                }
            } else if (gotP.piece == Point::emptyPiece) {
                continuousRingInRowOrange = 0;
                continuousRingInRowBlue = 0;
                continuousMarkerInRowOrange = 0;
                continuousMarkerInRowBlue = 0;
            }
            

            markerScoreBlue += 
            std::pow(weightSuccessiveMarker, continuousMarkerInRowBlue);
        
            markerScoreOrange += 
            std::pow(weightSuccessiveMarker, continuousMarkerInRowOrange);
        };

        auto checkFlipping = [&] () {
            if ((ringInRowOrange >= 1) && (ringInRowBlue == 0)) {
                flippedScoreOrange += (markerInRowBlue-markerInRowOrange);
                // additional security
                if (markerInRowBlue >= threshOfmarkerSecurity) {
                    flippedScoreOrange += weightSecurity*(markerInRowBlue-markerInRowOrange);
                }
            } else if ((ringInRowBlue >= 1) && (ringInRowOrange == 0)) {
                flippedScoreBlue += (markerInRowOrange-markerInRowBlue);
                // additional security
                if (markerInRowBlue >= threshOfmarkerSecurity) {
                    flippedScoreOrange += weightSecurity*(markerInRowOrange-markerInRowBlue);
                }
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
        markerScoreReturned = 
        markerScoreOrange - markerScoreBlue;
        flippedScoreReturned = flippedScoreOrange - flippedScoreBlue;
        contiguousMarkerScoreReturned = contiguousMarkerOrange - contiguousMarkerBlue;
        if (whosUtil == Game::blue) {
            // reverse sign if blue
            markerScoreReturned = -markerScoreReturned;
            flippedScoreReturned = -flippedScoreReturned;
        }

        std::shared_ptr<Player> orangePlayer = toCalculateOnGame.getPlayerFromColor(Game::orange);
        std::shared_ptr<Player> bluePlayer = toCalculateOnGame.getPlayerFromColor(Game::blue);

        // ring player score
        if (whosUtil == Game::orange) {
            ringWonScoreReturned = pow(successiveRingCollectIncrease, orangePlayer->ringWon) 
            - pow(bluePlayer->ringWon, successiveRingCollectIncrease);
        } else {
            ringWonScoreReturned = pow(successiveRingCollectIncrease, bluePlayer->ringWon) 
            - pow(orangePlayer->ringWon, successiveRingCollectIncrease);
        }

        // FIXME: try this ai doesn't finish rings first
        // combinedScore = combinedScore*(currentPlayerScore)*0.5;

        double combinedScore = 
        weigthRingMobility*mobilityRingsScoreReturned +
        weigthRingCentering*centeringRingScoreReturned +
        weightMarkerScore*markerScoreReturned +
        weightFlipped*flippedScoreReturned +
        weightRingWon*ringWonScoreReturned +
        weightContiguousMarker*contiguousMarkerScoreReturned;
        
        return combinedScore;
    }
}
