#include "Node.h"
#include "Game.h"
#include "Move.h"

#include <vector>

Node::Node(Game& gameStateInput, Node& parentInput) {
    gameState = &gameStateInput;
    parent = &parentInput;
    alpha = std::numeric_limits<double>::infinity();
    beta = -1*std::numeric_limits<double>::infinity();
    childrenDefined = false;
    childPicked = -1;
}

void Node::defineChildren() {
    childrenDefined = true;
    
}
