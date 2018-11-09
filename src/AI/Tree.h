#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include "../Game/Move.h"

#include <memory>

class Tree {
public:
    // DATA MEMBERS
    std::shared_ptr<Node> root;

    // MEMBER FUNCTIONS
    Tree();
    Tree(std::shared_ptr<Node> rootInput);

    // pick childs sets it as root
    Move pickChild(int indexOfChild);
    void pickChild(Move& moveForObtainingChild);

    // helper to find child
    static bool sameMoveInTuple(std::tuple<Move, std::shared_ptr<Node>> checkThisTuple, Move checkEqualToMove);

    int findInChildren(Move equlToThisMove);
};

#endif /* TREE_H */