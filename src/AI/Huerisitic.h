#ifndef HUERISITIC_H
#define HUERISITIC_H

#include "Node.h"
#include "../Game/Game.h"
#include "../Game/Move.h"

#include <tuple>
#include <memory>

namespace Huerisitic {
    // marker differnece 
    int markerDiff(std::shared_ptr<Game> g, Game::chanceType whosUtil);
    bool markerDiffComparator(std::tuple<Move, std::shared_ptr<Node>> tup1, 
    std::tuple<Move, std::shared_ptr<Node>> tup2, Game::chanceType whosUtil);

    // Placement
    double centeringRingScore(Point& toCalculateOnRing, int gameBoardSize);
    double centeringAllRingScore(Game& toCalculateOnGame, Game::chanceType whosUtil);
    double mobilityAllRingScore(Game& toCalculateOnGame, Game::chanceType whosUtil);

    // terminal utility
    double combinedUtility(Game& toCalculateOnGame, Game::chanceType whosUtil);
};

#endif /* HUERISITIC_H */