#ifndef NODE_H
#define NODE_H

#include "../Game/Game.h"
#include "../Game/Move.h"

#include <vector>
#include <tuple>
#include <memory>

class Node : public std::enable_shared_from_this<Node> {
public:
    // FEILDS
    // game knows players(rings vector, number of marker), board
    std::shared_ptr<Game> gameState;

    // all the tree stuff that a node should contain.
    std::shared_ptr<Node> parent;

    // children information
    int childPicked;
    bool childrenDefined;
    std::vector<std::tuple<Move, std::shared_ptr<Node>>> children;
    
    // function pointers needed
    typedef bool (*compareMoveNodeTupleFunction)
    (std::tuple<Move, std::shared_ptr<Node>>, std::tuple<Move, std::shared_ptr<Node>>);
    typedef double (*utilityOfGameFunction)(Game&);

    // FUNCTIONS
    // Node();
    Node(std::shared_ptr<Game> gameStateInput, std::shared_ptr<Node> parentInput);

    // define children in the vector.
    void defineChildren();

    // sorting probably for effecctive alpha beta pruning
    void sortChildren(compareMoveNodeTupleFunction comparer);

    // helper for define Children. Not too dependent on node.
    // generates permutation of removals
    // isThisFirstRemoveCheck of this time
    static std::vector<std::tuple<Move, std::shared_ptr<Game>>> keepCheckingRemovalOfRowAndRing(
    std::shared_ptr<Game> gameStateTillNow, Move& moveTillNow);
    // static std::vector<std::tuple<Move, Game>> keepCheckingRemovalOfRowAndRing(
    //     Game& gameStateTillNow, Move& moveTillNow, bool isThisFirstRemoveCheck);
    static void flipMakeChildPushBack (std::shared_ptr<Game> gameStateInput, Move& moveInput, std::shared_ptr<Node> self, 
    std::vector<std::tuple<Move, std::shared_ptr<Node>>>& childrenList);
    static void seeSMthenRSREX(std::shared_ptr<Game> gameTillNow, Move& moveTillNow, 
    std::shared_ptr<Node> self, std::vector<std::tuple<Move, std::shared_ptr<Node>>>& childrenList);

    // minMax Procedures
    int minMaxDepthCutOffSortedAlphaBetaPruning(double alpha, 
    double beta, int depthLeftTillCutOff, int treeLevel, 
    utilityOfGameFunction terminalUtility, compareMoveNodeTupleFunction sortComparator);

    // minMax Helpers
    void ifNotThenDefineSortChildren(compareMoveNodeTupleFunction sortComparator);

    void deleteParentAndCousins();
    void deleteChildrenExceptBest();
    void deleteAllChildrenAndSelf();
};

#endif /* NODE_H */