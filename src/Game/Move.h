#ifndef MOVE_H
#define MOVE_H

#include "Operation.h"

#include <string>
#include <vector>
#include <tuple>

class Move {
public:
    /* FIELDS */
    // operations like P, S, M, RS, RE, X.
    
    std::vector<Operation> operationSequence;
    bool operator ==(const Move& other);

    /* FUNCTIONS */

    // constructor converts string of form of 
    // hexCoord to Move object(which stores in form of TriLinearCoord)
    Move();
    Move(std::string sFromTerminal, bool isHex);
    Move(std::vector<Operation> operationSeq);
    
    // append second move after the first
    void append(Move& secondMove);

    // convert Move object to string.
    std::string toStr(bool isHex);
};

#endif /* MOVE_H */
