#ifndef NODE_H
#define NODE_H

#include "Game.h"
#include "Move.h"

#include <vector>
#include <tuple>

class Node {
    // FEILDS
    // game knows players(rings vector, number of marker), board
    Game gameState;

    // all the tree stuff that a node should contain.
    Node* parent;

    // children information
    int childPicked;
    bool childrenDefined;
    std::vector<std::tuple<Move, Node*>> children;

    // for alpha beta pruning
    double alpha;
    double beta;
    
    // FUNCTIONS
    Node(Game& gameStateInput, Node& parentInput);

    // define children in the vector.
    void defineChildren();

    // helper for define Children. Not too dependent on node.
    // generates permutation of removals
    // isThisFirstRemoveCheck of this time
    static std::vector<std::tuple<Move, Game>> keepCheckingRemovalOfRowAndRing 
    (Game& gameStateTillNow, Move& moveTillNow, bool isThisFirstRemoveCheck);
    static void flipMakeChildPushBack (Game& gameStateInput, Move& moveInput, Node* self, 
    std::vector<std::tuple<Move, Node*>>& childrenList);
    static void seeSMthenRSREX(Game& gameTillNow, Move& moveTillNow, 
    Node* self, std::vector<std::tuple<Move, Node*>>& childrenList);
};

#endif /* NODE_H */