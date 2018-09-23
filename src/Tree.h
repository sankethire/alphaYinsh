#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include "Move.h"

class Tree {
public:
    // DATA MEMBERS
    Node* root;

    // MEMBER FUNCTIONS
    Tree(Node* rootInput);

    // pick childs sets it as root
    Move pickChild(int indexOfChild);
    void pickChild(Move moveForObtainingChild);
};

#endif /* TREE_H */