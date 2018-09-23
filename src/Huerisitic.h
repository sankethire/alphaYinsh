#ifndef HUERISITIC_H
#define HUERISITIC_H

#include "Game.h"
#include "Board.h"
#include "Move.h"

#include <tuple>

namespace Huerisitic {
    // marker differnece 
    int markerDiff(Game& g);
    bool markerDiffComparator(std::tuple<Move, Game> tup1, std::tuple<Move, Game> tup2);
};

#endif /* HUERISITIC_H */