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
    
    // function pointers needed
    typedef bool (*compareMoveNodeTupleFunction)(std::tuple<Move, Node>, std::tuple<Move, Node>);
    typedef int (*utilityOfGameFunction)(Game&);

    // FUNCTIONS
    Node(Game& gameStateInput, Node& parentInput);

    // define children in the vector.
    void defineChildren();

    // sorting probably for effecctive alpha beta pruning
    void sortChildren(compareMoveNodeTupleFunction comparer);

    // helper for define Children. Not too dependent on node.
    // generates permutation of removals
    // isThisFirstRemoveCheck of this time
    static std::vector<std::tuple<Move, Game>> keepCheckingRemovalOfRowAndRing 
    (Game& gameStateTillNow, Move& moveTillNow, bool isThisFirstRemoveCheck);
    static void flipMakeChildPushBack (Game& gameStateInput, Move& moveInput, Node* self, 
    std::vector<std::tuple<Move, Node*>>& childrenList);
    static void seeSMthenRSREX(Game& gameTillNow, Move& moveTillNow, 
    Node* self, std::vector<std::tuple<Move, Node*>>& childrenList);

    // minMax Procedures
    int minMaxDepthCutOffSortedAlphaBetaPruning(int alpha, 
    int beta, int depthLeftTillCutOff, int treeLevel, 
    utilityOfGameFunction terminalUtility, compareMoveNodeTupleFunction sortComparator);

    // minMax Helpers
    void ifNotThenDefineSortChildren(compareMoveNodeTupleFunction sortComparator);
};

#endif /* NODE_H */