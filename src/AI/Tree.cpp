#include "Tree.h"
#include "Node.h"
#include "../Game/Move.h"

#include <tuple>
#include <vector>
#include <algorithm>
#include <iostream>

Tree::Tree() {}

Tree::Tree(std::shared_ptr<Node> rootInput) {
    root = rootInput;
}

Move Tree::pickChild(int indexOfChild) {
    std::tuple<Move, std::shared_ptr<Node>>& moveNodeFromTuple = root->children[indexOfChild];
    std::shared_ptr<Node> nextRootToSet = std::get<1>(moveNodeFromTuple);
    root = nextRootToSet;
    return std::get<0>(moveNodeFromTuple);
}

int Tree::findInChildren(Move equlToThisMove) {
    for (int i=0; i<root->children.size(); i++) {
        if (std::get<0>(root->children[i]) == equlToThisMove) {
            return i;
        }
    }
    return -1;
}

void Tree::pickChild(Move& moveForObtainingChild) {

    int indexOfChild = findInChildren(moveForObtainingChild);

    if (indexOfChild != -1) {
        std::shared_ptr<Node> nextRootToSet = std::get<1>(root->children[indexOfChild]);
        root->childPicked = indexOfChild;
        root = nextRootToSet;
    } else {
        // we didn't generate this move in possible moves
        std::shared_ptr<Game> choosenGame = root->gameState->clone();
        std::shared_ptr<Node> choosenNode = std::make_shared<Node>(choosenGame, root);
        root->children.push_back(std::make_tuple(moveForObtainingChild, choosenNode));
        root->childPicked = (root->children.size()-1);

        // TODO: chance flips here in case move not found in possible move
        // generated by us
        choosenNode->gameState->executeMove(moveForObtainingChild);
        choosenNode->gameState->chanceFlip();
        root = choosenNode;
    }
}

bool Tree::sameMoveInTuple(std::tuple<Move, std::shared_ptr<Node>> checkThisTuple, Move checkEqualToMove) {
    return (checkEqualToMove == std::get<0>(checkThisTuple));
}