#include "Node.h"
#include "Huerisitic.h"
#include "Game.h"
#include "Move.h"

#include <vector>
#include <tuple>
#include <algorithm>

Node::Node(Game& gameStateInput, Node& parentInput) {
    gameState = gameStateInput;
    parent = &parentInput;
    alpha = std::numeric_limits<double>::infinity();
    beta = -1*std::numeric_limits<double>::infinity();
    childrenDefined = false;
    childPicked = -1;
}

std::vector<std::tuple<Move, Game>> Node::keepCheckingRemovalOfRowAndRing
(Game& gameStateTillNow, Move& moveTillNow, bool isThisFirstRemoveCheck) {

    std::vector<std::tuple<Move, Game>> vecToReturn;
    std::vector<Move> possibleRowRemoveMoves = gameStateTillNow.contiguousMarker
    (gameStateTillNow.numberOfMarkersToRemove, gameStateTillNow.chance);

    if (possibleRowRemoveMoves.size() != 0) {
        for (Move eachRowRemoval: possibleRowRemoveMoves) {

            std::vector<Move> possibleRingRemoveMoves = gameStateTillNow.possibleRingRemoval
            (gameStateTillNow.chance);
            std::vector<std::tuple<Move, Game>> tempCombinedVec;

            for (Move eachRingRemoval: possibleRingRemoveMoves) {
                // TODO: just want to use shallow copy here.
                // just keeps record of fullMove. appends after appends
                Move tempMove;
                if (isThisFirstRemoveCheck) {
                    tempMove = eachRingRemoval;
                } else {
                    tempMove = moveTillNow;
                    tempMove.append(eachRingRemoval);
                }

                Game tempGameState = gameStateTillNow.clone();
                // This tempRSREX actually executes.
                Move tempRSREX = eachRowRemoval;
                tempRSREX.append(eachRingRemoval);
                tempGameState.executeMove(tempRSREX);

                std::vector<std::tuple<Move, Game>> tempReturnedVec;
                // TODO: multiple game won checks need to be introduced.
                if (tempGameState.hasSomeoneWon()) {
                    tempReturnedVec.push_back(std::make_tuple(tempMove, tempGameState));
                } else {
                    tempReturnedVec = keepCheckingRemovalOfRowAndRing
                    (tempGameState, tempMove, false);
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

void Node::flipMakeChildPushBack (Game& gameStateInput, Move& moveInput, Node* self, 
std::vector<std::tuple<Move, Node*>>& childrenList) {
    // TODO: chance filps here
    gameStateInput.chanceFlip();
    Node* childNode = new Node(gameStateInput, *self);
    childrenList.push_back(std::make_tuple(moveInput, childNode));
}

void Node::seeSMthenRSREX(Game& gameTillNow, Move& moveTillNow, 
Node* self, std::vector<std::tuple<Move, Node*>>& childrenList) {
    std::vector<Move> possibleSMMoves = 
    gameTillNow.possibleMovementOfRings(gameTillNow.chance);
    for (Move eachSMMove: possibleSMMoves) {

        Game tempGameStateFromTuple1 = gameTillNow.clone();
        tempGameStateFromTuple1.executeMove(eachSMMove);
        Move tempMoveStateFromTuple1 = moveTillNow;
        tempMoveStateFromTuple1.append(eachSMMove);

        std::vector<std::tuple<Move, Game>> possibleRemove2 =
        Node::keepCheckingRemovalOfRowAndRing
        (tempGameStateFromTuple1, tempMoveStateFromTuple1, true);

        if (possibleRemove2.size() != 0) {
            for (std::tuple<Move, Game> moveGameTuple2: possibleRemove2) {
                Game& gameFromTuple2 = std::get<1>(moveGameTuple2);
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
    
    if (gameState.phase == Game::placement) {
        std::vector<Move> possiblePlaceMoves = gameState.possiblePlacement();
        for (Move eachMove : possiblePlaceMoves) {
            Game tempGameState = gameState.clone();
            tempGameState.executeMove(eachMove);
            flipMakeChildPushBack(tempGameState, eachMove, this, children);
        }
    } else {
        Move dummyMove = Move();
        std::vector<std::tuple<Move, Game>> possibleRemove1 = 
        Node::keepCheckingRemovalOfRowAndRing(gameState, dummyMove, true);

            // although it is tried that keepCheckingRemovalOfRowAndRing 
            // returns same game state and move in case nothing can be done 
            // but still 0 case is handled 
            if (possibleRemove1.size() != 0) {
                for (std::tuple<Move, Game> moveGameTuple1: possibleRemove1) {
                    // TODO: check has won here.
                    Game& gameFromTuple1 = std::get<1>(moveGameTuple1);
                    Move& moveFromTuple1 = std::get<0>(moveGameTuple1);

                    if (gameFromTuple1.hasSomeoneWon()) {
                        flipMakeChildPushBack
                        (gameFromTuple1, moveFromTuple1, this, children);
                        continue;
                    }

                    seeSMthenRSREX(gameFromTuple1, moveFromTuple1, this, children);
                }
            // first removal sequence not possible
            } else {
                seeSMthenRSREX(gameState, dummyMove, this, children);
            }
    }
}

void Node::sortChildren(compareMoveNodeTupleFunction comparer) {
    std::sort(children.begin(), children.end(), comparer);
}
