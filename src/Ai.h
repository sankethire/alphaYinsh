#ifndef AI_H
#define AI_H

#include "Tree.h"

#include <sstream>

class Ai {
public:
    // DATA MEMBERS
    // given by server
    int playerId, boardSize, timeLimit;

    // alpha beta pruning related
    int depthCutOff;

    Tree treeForMinMax;

    // MEMBER FUNCTIONS
    Ai(int playerIdInput, int boardSizeInput, int timeLimitInput, 
    int depthCutOffInput);

    void doMinMax(double infi);
    void shiftInTree(std::stringstream& ss);
    void startBot();
};

#endif /* AI_H */