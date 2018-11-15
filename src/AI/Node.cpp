#include "Node.h"
#include "Huerisitic.h"
#include "../Game/Game.h"
#include "../Game/Move.h"

#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <memory>

// Node::Node() {
//     gameState = Game();
//     parent = NULL;
//     childrenDefined = false;
//     childPicked = -1;
// }

Node::Node(std::shared_ptr<Game> gameStateInput, std::shared_ptr<Node> parentInput) {
    gameState = gameStateInput;
    parent = parentInput;
    childrenDefined = false;
    childPicked = -1;
}

std::vector<std::tuple<Move, std::shared_ptr<Game>>> Node::keepCheckingRemovalOfRowAndRing(
    std::shared_ptr<Game> gameStateTillNow, Move& moveTillNow) {

    std::vector<std::tuple<Move, std::shared_ptr<Game>>> vecToReturn;
    std::vector<Move> possibleRowRemoveMoves = gameStateTillNow->contiguousMarker
    (gameStateTillNow->numberOfMarkersToRemove, gameStateTillNow->chance);

    if (possibleRowRemoveMoves.size() != 0) {
        for (Move eachRowRemoval: possibleRowRemoveMoves) {

            std::vector<Move> possibleRingRemoveMoves = gameStateTillNow->possibleRingRemoval
            (gameStateTillNow->chance);
            std::vector<std::tuple<Move, std::shared_ptr<Game>>> tempCombinedVec;

            for (Move eachRingRemoval: possibleRingRemoveMoves) {
                // TODO: just want to use shallow copy here.
                // just keeps record of fullMove. appends after appends
                Move tempMove;
                // if (moveTillNow.operationSequence.size() == 0) {
                //     tempMove = eachRowRemoval;
                //     tempMove.append(eachRingRemoval);
                // } else {
                tempMove = moveTillNow;
                tempMove.append(eachRowRemoval);
                tempMove.append(eachRingRemoval);
                // }

                std::shared_ptr<Game> tempGameState = gameStateTillNow->clone();
                // This tempRSREX actually executes.
                Move tempRSREX = eachRowRemoval;
                tempRSREX.append(eachRingRemoval);
                tempGameState->executeMove(tempRSREX);

                std::vector<std::tuple<Move, std::shared_ptr<Game>>> tempReturnedVec;
                // TODO: multiple game won checks need to be introduced.
                if (tempGameState->hasSomeoneWon()) {
                    tempReturnedVec.push_back(std::make_tuple(tempMove, tempGameState));
                } else {
                    // tempReturnedVec = keepCheckingRemovalOfRowAndRing
                    // (tempGameState, tempMove, false);
                    tempReturnedVec = keepCheckingRemovalOfRowAndRing
                    (tempGameState, tempMove);
                }

                tempCombinedVec.insert
                (tempCombinedVec.end(), tempReturnedVec.begin(),  tempReturnedVec.end());
            }

            vecToReturn.insert
            (vecToReturn.end(), tempCombinedVec.begin(), tempCombinedVec.end());
        }
    } else {
        vecToReturn.push_back(std::make_tuple(moveTillNow, gameStateTillNow));
    }
    return vecToReturn;
}

void Node::flipMakeChildPushBack (std::shared_ptr<Game> gameStateInput, Move& moveInput, 
std::shared_ptr<Node> self, 
std::vector<std::tuple<Move, std::shared_ptr<Node>>>& childrenList) {
    // TODO: chance filps here
    gameStateInput->chanceFlip();
    std::shared_ptr<Node> childNode = std::make_shared<Node>(gameStateInput, self);
    childrenList.push_back(std::make_tuple(moveInput, childNode));
}

void Node::seeSMthenRSREX(std::shared_ptr<Game> gameTillNow, Move& moveTillNow, 
std::shared_ptr<Node> self, std::vector<std::tuple<Move, 
std::shared_ptr<Node>>>& childrenList) {
    std::vector<Move> possibleSMMoves = 
    gameTillNow->possibleMovementOfRings(gameTillNow->chance);
    for (Move eachSMMove: possibleSMMoves) {

        std::shared_ptr<Game> tempGameStateFromTuple1 = gameTillNow->clone();
        tempGameStateFromTuple1->executeMove(eachSMMove);
        Move tempMoveStateFromTuple1 = moveTillNow;
        tempMoveStateFromTuple1.append(eachSMMove);

        // std::vector<std::tuple<Move, Game>> possibleRemove2 =
        // Node::keepCheckingRemovalOfRowAndRing
        // (tempGameStateFromTuple1, tempMoveStateFromTuple1, true);
        std::vector<std::tuple<Move, std::shared_ptr<Game>>> possibleRemove2 =
        Node::keepCheckingRemovalOfRowAndRing
        (tempGameStateFromTuple1, tempMoveStateFromTuple1);

        if (possibleRemove2.size() != 0) {
            for (std::tuple<Move, std::shared_ptr<Game>> moveGameTuple2: possibleRemove2) {
                std::shared_ptr<Game> gameFromTuple2 = std::get<1>(moveGameTuple2);
                Move& moveFromTuple2 = std::get<0>(moveGameTuple2);
                flipMakeChildPushBack
                (gameFromTuple2, moveFromTuple2, self, childrenList);
            }
        // second removal sequence not possible
        } else {
            // 0 case handled here as well. most probably unnecessary
            flipMakeChildPushBack
            (tempGameStateFromTuple1, tempMoveStateFromTuple1, self, childrenList);
        }
    }
}

void Node::defineChildren() {
    childrenDefined = true;
    
    if (gameState->movesLeftTillPlacementEnd >= 1) {
        std::vector<Move> possiblePlaceMoves;
        possiblePlaceMoves.reserve(85*sizeof(Move));
        possiblePlaceMoves = gameState->possiblePlacement();
        for (Move eachMove : possiblePlaceMoves) {
            std::shared_ptr<Game> tempGameState = gameState->clone();
            tempGameState->executeMove(eachMove);
            flipMakeChildPushBack(tempGameState, eachMove, 
            shared_from_this(), children);
        }
    } else {
        Move dummyMove = Move();
        // std::vector<std::tuple<Move, Game>> possibleRemove1 = 
        // Node::keepCheckingRemovalOfRowAndRing(gameState, dummyMove, true);
        std::vector<std::tuple<Move, std::shared_ptr<Game>>> possibleRemove1 = 
        Node::keepCheckingRemovalOfRowAndRing(gameState, dummyMove);

            // although it is tried that keepCheckingRemovalOfRowAndRing 
            // returns same game state and move in case nothing can be done 
            // but still 0 case is handled 
            if (possibleRemove1.size() != 0) {
                for (std::tuple<Move, std::shared_ptr<Game>> moveGameTuple1: possibleRemove1) {
                    // TODO: check has won here.
                    std::shared_ptr<Game> gameFromTuple1 = std::get<1>(moveGameTuple1);
                    Move& moveFromTuple1 = std::get<0>(moveGameTuple1);

                    if (gameFromTuple1->hasSomeoneWon()) {
                        flipMakeChildPushBack
                        (gameFromTuple1, moveFromTuple1, 
                        shared_from_this(), children);
                        continue;
                    } else {
                        seeSMthenRSREX(gameFromTuple1, moveFromTuple1, 
                        shared_from_this(), children);
                    }

                }
            // first removal sequence not possible
            } else {
                seeSMthenRSREX(gameState, dummyMove, 
                shared_from_this(), children);
            }
    }
}

void Node::sortChildren(compareMoveNodeTupleFunction comparer, 
Game::chanceType whosUtil) {
    auto comparerModified = [&] (std::tuple<Move, std::shared_ptr<Node>> tup1,
    std::tuple<Move, std::shared_ptr<Node>> tup2) {
        return comparer(tup1, tup2, whosUtil);
    };
    std::sort(children.begin(), children.end(), comparerModified);
}

void Node::ifNotThenDefineSortChildren(compareMoveNodeTupleFunction sortComparator, 
Game::chanceType whosUtil) {
    if (!childrenDefined) {
        defineChildren();
        sortChildren(sortComparator, whosUtil);
    }
}

int Node::minMaxDepthCutOffSortedAlphaBetaPruning(double alpha, 
double beta, int depthLeftTillCutOff, int treeLevel, Game::chanceType whosUtil, 
utilityOfGameFunction terminalUtility, compareMoveNodeTupleFunction sortComparator) {
    // odd tree level max node else min
    // at depthLeftTillCutOff 0 return utility
    // TODO: pass placement movement different utility
    // if (gameState->hasSomeoneWon()) {
    //     return terminalUtility(*gameState);
    // }
    if (depthLeftTillCutOff == 0 || gameState->hasSomeoneWon()) {
        return terminalUtility(*gameState, whosUtil);
    }

    if (treeLevel%2 == 1) {
        // Max Node
        ifNotThenDefineSortChildren(sortComparator, whosUtil);
        for (int i=0; i<children.size(); i++) {
            std::tuple<Move, std::shared_ptr<Node>> currentChild = children[i];
            Move moveFromTuple = std::get<0>(currentChild);
            std::shared_ptr<Node> nodeFromTuple = std::get<1>(currentChild);
            double returnedValue;
            if (moveFromTuple.operationSequence[0].opcode != Operation::RS) {
                returnedValue = nodeFromTuple->minMaxDepthCutOffSortedAlphaBetaPruning(
                alpha, beta, depthLeftTillCutOff-1, treeLevel+1, whosUtil, 
                terminalUtility, sortComparator);
            } else {
                returnedValue = terminalUtility(*(nodeFromTuple->gameState), whosUtil);
            }

            if (returnedValue > alpha) {
                alpha = returnedValue;
                childPicked = i;
            }
            if (alpha>=beta) {
                return alpha;
            }
        }
        return alpha;
    } else {
        // Min Node
        ifNotThenDefineSortChildren(sortComparator, whosUtil);
        for (int i=0; i<children.size(); i++) {
            std::tuple<Move, std::shared_ptr<Node>> currentChild = children[i];
            Move moveFromTuple = std::get<0>(currentChild);
            std::shared_ptr<Node> nodeFromTuple = std::get<1>(currentChild);
            double returnedValue;
            if (moveFromTuple.operationSequence[0].opcode != Operation::RS) {
                returnedValue = nodeFromTuple->minMaxDepthCutOffSortedAlphaBetaPruning(
                alpha, beta, depthLeftTillCutOff-1, treeLevel+1, whosUtil, 
                terminalUtility, sortComparator);
            } else {
                returnedValue = terminalUtility(*(nodeFromTuple->gameState), whosUtil);
            }
            if (returnedValue < beta) {
                beta = returnedValue;
                childPicked = i;
            }
            if (alpha>=beta) {
                return beta;
            }
        }
        return beta;
    }
}


void Node::deleteChildrenExceptBest() {
    for (int i=0; i<children.size(); i++) {
        if (i != childPicked) {
            std::shared_ptr<Node> eachChild = std::get<1>(children[i]);
            eachChild->deleteAllChildrenAndSelf();
            // std::cerr << "each Child " << i << " - " << eachChild.use_count() << std::endl;
            eachChild.reset();
        }
    }
    // std::cerr << "its parent " << parent.use_count() << std::endl;
    parent.reset();
    shared_from_this().reset();
}

void Node::deleteAllChildrenAndSelf() {
    for (int i=0; i<children.size(); i++) {
        std::shared_ptr<Node> eachChild = std::get<1>(children[i]);
        eachChild->deleteAllChildrenAndSelf();
        // std::cerr << "each Child " << i << " - " << eachChild.use_count() << std::endl;
        eachChild.reset();
    }
    // std::cerr << "its parent " << parent.use_count() << std::endl;
    parent.reset();
    shared_from_this().reset();
}

void Node::deleteParentAndCousins() {
    if (parent != NULL) {
        parent->deleteChildrenExceptBest();
    }
    parent.reset();
    parent = NULL;
}
