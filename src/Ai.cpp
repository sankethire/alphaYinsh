#include "Ai.h"
#include "Tree.h"
#include "Game.h"
#include "Huerisitic.h"
#include "Move.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

Ai::Ai(int playerIdInput, int boardSizeInput, 
int timeLimitInput, int depthCutOffInput) {
    playerId = playerIdInput;
    boardSize = boardSizeInput;
    timeLimit = timeLimitInput;
    depthCutOff = depthCutOffInput;
}

void Ai::startBot() {
    double inf = std::numeric_limits<double>::infinity();
    Node* nullParent = NULL;
    Game* startingBoard = new Game(boardSize, 5, 3, 5);
    Node* startingNode = new Node(*startingBoard, *nullParent);
    treeForMinMax = Tree(startingNode);

    std::stringstream ss;
    std::ofstream outfile;
    outfile.open("prevGameMoves.txt",  std::ios::out | std::ios::trunc);

    auto doMinMax = [&] () {
        treeForMinMax.root->minMaxDepthCutOffSortedAlphaBetaPruning(
        -inf, inf, depthCutOff, 1, 
        Huerisitic::combinedUtility, Huerisitic::markerDiffComparator);
    };

    auto shiftInTree = [&] () {
        while (treeForMinMax.root->gameState.hasSomeoneWon()) {
            std::string moveInput;
            doMinMax();
            Move toDoMove = treeForMinMax.pickChild(treeForMinMax.root->childPicked);
            std::cout << toDoMove.toStr(true) << std::endl;
            ss << moveInput;
            ss << toDoMove.toStr(true) << std::endl;
            if (treeForMinMax.root->gameState.hasSomeoneWon()) {
                break;
            }
            getline(std::cin, moveInput);
            Move tempMove = Move(moveInput, true);
            treeForMinMax.pickChild(tempMove);
        }
    };

    if (playerId == 1) {
        shiftInTree();
    } else {
        std::string moveInputFirst;
        getline(std::cin, moveInputFirst);
        Move tempMove = Move(moveInputFirst, true);
        treeForMinMax.pickChild(tempMove);
        shiftInTree();
    }

    outfile << ss.str();
    outfile.close();
}

int main(int argc, char** argv) {
    int player_id, board_size, time_limit;
    // Get input from server about game specifications
    std::cin >> player_id >> board_size >> time_limit;
    Ai alphaYinsh = Ai(player_id, board_size, time_limit, 4);
    alphaYinsh.startBot();
}