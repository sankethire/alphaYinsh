#ifndef HUERISITIC_H
#define HUERISITIC_H

#include "Game.h"
#include "Board.h"
#include "Move.h"
#include "Point.h"

#include <tuple>

namespace Huerisitic {
    // marker differnece 
    int markerDiff(Game& g);
    bool markerDiffComparator(std::tuple<Move, Game> tup1, std::tuple<Move, Game> tup2);

    // Placement
    double centeringRingScore(Point& toCalculateOnRing, int gameBoardSize);
    double centeringAllRingScore(Game& toCalculateOnGame);
    double mobilityAllRingScore(Game& toCalculateOnGame);

    // terminal utility
    double combinedUtility(Game& toCalculateOnGame);
};

#endif /* HUERISITIC_H */