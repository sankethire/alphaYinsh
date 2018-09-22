#ifndef NODE_H
#define NODE_H

#include "Game.h"
#include "Move.h"

#include <vector>

class Node {
    // FEILDS
    // game knows players(rings vector, number of marker), board
    Game* gameState;

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
};

#endif /* NODE_H */