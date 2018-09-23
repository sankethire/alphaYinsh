#include "Huerisitic.h"
#include "Game.h"
#include "Board.h"
#include "Move.h"

#include <tuple>

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

bool Huerisitic::markerDiffComparator(std::tuple<Move, Game> tup1, 
std::tuple<Move, Game> tup2) {
    Game& g1 = std::get<1>(tup1);
    Game& g2 = std::get<1>(tup2);
    return (markerDiff(g1) < markerDiff(g2));
}
