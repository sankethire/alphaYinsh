#include "Ai.h"
#include "Tree.h"
#include "Game.h"
#include "Huerisitic.h"
#include "Move.h"
#include "Point.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <limits>

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
    Game* startingGame = new Game(boardSize, 5, 3, 5);
    Node* startingNode = new Node(*startingGame, *nullParent);
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
        while (!(treeForMinMax.root->gameState.hasSomeoneWon())) {
            std::string moveInput;
            doMinMax();
            Move toDoMove = treeForMinMax.pickChild(treeForMinMax.root->childPicked);
            std::cout << toDoMove.toStr(true) << std::endl;
            std::cerr << treeForMinMax.root->gameState.board.toStringBoard();
            ss << moveInput << std::endl;
            ss << toDoMove.toStr(true) << std::endl;
            if (treeForMinMax.root->gameState.hasSomeoneWon()) {
                break;
            }
            getline(std::cin, moveInput);
            Move tempMove = Move(moveInput, true);
            treeForMinMax.pickChild(tempMove);
            std::cerr << treeForMinMax.root->gameState.board.toStringBoard();
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

    delete startingGame;
    delete startingNode;
    outfile << ss.str();
    outfile.close();
}

int main(int argc, char** argv) {
    Point::defineTriLinearDirection();
    int player_id, board_size, time_limit;
    // Get input from server about game specifications
    // FIXME: Change this
    // std::cin >> player_id >> board_size >> time_limit;
    player_id = 1; 
    board_size = 5; 
    time_limit = 120;
    Ai alphaYinsh = Ai(player_id, board_size, time_limit, 2);
    alphaYinsh.startBot();
}