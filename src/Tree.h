#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include "Move.h"

class Tree {
public:
    // DATA MEMBERS
    Node* root;

    // MEMBER FUNCTIONS
    Tree();
    Tree(Node* rootInput);

    // pick childs sets it as root
    Move pickChild(int indexOfChild);
    void pickChild(Move& moveForObtainingChild);

    // helper to find child
    static bool sameMoveInTuple(std::tuple<Move, Node*> checkThisTuple, Move checkEqualToMove);

    int findInChildren(Move equlToThisMove);
};

#endif /* TREE_H */