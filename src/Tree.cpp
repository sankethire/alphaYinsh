#include "Tree.h"
#include "Node.h"
#include "Move.h"

#include <tuple>

Tree::Tree(Node* rootInput) {
    rootInput = rootInput;
}

Move Tree::pickChild(int indexOfChild) {
    std::tuple<Move, Node*> moveNodeFromTuple = root->children[indexOfChild];
    Node* nextRootToSet = std::get<1>(moveNodeFromTuple);
    return std::get<0>(moveNodeFromTuple);
}

void Tree::pickChild(Move moveForObtainingChild) {
    
}
