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
    

    /* FUNCTIONS */

    // constructor converts string of form of 
    // hexCoord to Move object(which stores in form of TriLinearCoord)
    Move(std::string sFromTerminal);
    Move(std::vector<Operation> operationSeq);

    // convert Move object to string.
    std::string toStr();
};

#endif /* MOVE_H */