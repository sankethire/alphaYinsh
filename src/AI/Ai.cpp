#include "Ai.h"
#include "Tree.h"
#include "Node.h"
#include "../Game/Game.h"
#include "Huerisitic.h"
#include "../Game/Move.h"
#include "../Game/Point.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <limits>
#include <memory>

Ai::Ai(int playerIdInput, int boardSizeInput, int continousMarkerInput, 
int timeLimitInput, int depthCutOffInput) {
    playerId = playerIdInput;
    boardSize = boardSizeInput;
    continousMarker = continousMarkerInput;
    timeLimit = timeLimitInput;
    depthCutOff = depthCutOffInput;
}

void Ai::doMinMax(double infi) {
    treeForMinMax.root->minMaxDepthCutOffSortedAlphaBetaPruning(
    -infi, infi, depthCutOff, 1, 
    Huerisitic::combinedUtility, Huerisitic::markerDiffComparator);
};

void Ai::shiftInTree(std::stringstream& ss) {
    double inf = std::numeric_limits<double>::infinity();
    while (!(treeForMinMax.root->gameState->hasSomeoneWon())) {
        doMinMax(inf);
        Move toDoMove = treeForMinMax.pickChild(treeForMinMax.root->childPicked);
        std::cout << toDoMove.toStr(true) << std::endl;
        std::cerr << "-----------------------------------" << std::endl;
        std::cerr << toDoMove.toStr(true) << std::endl;
        std::cerr << treeForMinMax.root->gameState->board->toStringBoard();
        std::cerr << "-----------------------------------" << std::endl;
        treeForMinMax.root->deleteParentAndCousins();
        ss << toDoMove.toStr(true) << std::endl;
        if (treeForMinMax.root->gameState->hasSomeoneWon()) {
            break;
        }

        std::string moveInput = "";
        while (moveInput == "") {
            std::getline(std::cin, moveInput);
        }
        Move tempMove = Move(moveInput, true);
        treeForMinMax.pickChild(tempMove);
        ss << moveInput << std::endl;
        std::cerr << "-----------------------------------" << std::endl;
        std::cerr << tempMove.toStr(true) << std::endl;
        std::cerr << treeForMinMax.root->gameState->board->toStringBoard();
        std::cerr << "-----------------------------------" << std::endl;
        treeForMinMax.root->deleteParentAndCousins();
    }
};

void Ai::startBot() {
    std::shared_ptr<Node> nullParent = NULL;
    std::shared_ptr<Game> startingGame = std::make_shared<Game>(boardSize, boardSize, 3, continousMarker);
    std::shared_ptr<Node> startingNode = std::make_shared<Node>(startingGame, nullParent);
    treeForMinMax = Tree(startingNode);
    nullParent.reset();
    startingGame.reset();
    startingNode.reset();

    std::stringstream sst;
    std::ofstream outfile;
    outfile.open("prevGameMoves.txt",  std::ios::out | std::ios::trunc);    

    if (playerId == 1) {
        shiftInTree(sst);
    } else {
        std::string moveInputFirst = "";
        while (moveInputFirst == "") {
            getline(std::cin, moveInputFirst);
        }
        Move tempMove = Move(moveInputFirst, true);
        treeForMinMax.pickChild(tempMove);
        shiftInTree(sst);
    }

    outfile << sst.str();
    outfile.close();
    treeForMinMax.root->deleteAllChildrenAndSelf();
}

int main(int argc, char** argv) {
    Point::defineTriLinearDirection();
    int player_id, board_size, seq_len, time_limit;
    // Get input from server about game specifications
    // FIXME: Change this
    std::cin >> player_id >> board_size >> time_limit >> seq_len;
    // player_id = 1;
    // board_size = 5; 
    // time_limit = 120;
    // seq_len = 5;
    Ai alphaYinsh = Ai(player_id, board_size, seq_len, time_limit, 3);
    alphaYinsh.startBot();
}