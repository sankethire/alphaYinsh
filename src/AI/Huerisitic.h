#ifndef HUERISITIC_H
#define HUERISITIC_H

#include "Node.h"
#include "../Game/Game.h"
#include "../Game/Move.h"

#include <tuple>
#include <memory>

namespace Huerisitic {
    // marker differnece 
    int markerDiff(std::shared_ptr<Game> g);
    bool markerDiffComparator(std::tuple<Move, std::shared_ptr<Node>> tup1, 
    std::tuple<Move, std::shared_ptr<Node>> tup2);

    // Placement
    double centeringRingScore(Point& toCalculateOnRing, int gameBoardSize);
    double centeringAllRingScore(Game& toCalculateOnGame);
    double mobilityAllRingScore(Game& toCalculateOnGame);

    // terminal utility
    double combinedUtility(Game& toCalculateOnGame);
};

#endif /* HUERISITIC_H */