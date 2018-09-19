#include "Player.h"
#include "Point.h"
#include "Board.h"

#include <vector>

Player::Player(Board& playBoard) {
    ringWon = 0;
    markerOwn = 0;
    playingBoard = &playBoard;
}

void Player::addRing(Point ringToAdd) {
    if (ringToAdd.piece = Point::ring) {
        ringLeft.push_back(ringToAdd);
    } else {
        std::invalid_argument("Added Non-Ring to ring list in addRing");
    }
}

void Player::addRing(int ringToRemoveX, int ringToRemoveY) {
    Point tempPoint = playingBoard->getPointTriLinear(ringToRemoveX, ringToRemoveY);
    addRing(tempPoint);
}

void Player::removeRing(int ringToRemoveX, int ringToRemoveY) {
    std::tuple<int, int> tempCoordTuple;
    for (int i=0; i<ringLeft.size(); i++) {
        Point tempPoint = ringLeft[i];
        tempCoordTuple = tempPoint.triLinearCoord;
        if ((ringToRemoveX == std::get<0>(tempCoordTuple)) 
        && (ringToRemoveY == std::get<1>(tempCoordTuple))) {
            ringLeft.erase(ringLeft.begin()+i);
            ringWon += 1;
            return;
        }
    }
    throw std::invalid_argument("No ring in ringLeft could be removed: Player.cpp");
}

void Player::removeRing(Point ringToRemove) {
    std::tuple<int, int> tempTuple = ringToRemove.triLinearCoord;
    removeRing(std::get<0>(tempTuple), std::get<1>(tempTuple));
}

