#include "Move.h"
#include "Operation.h"
#include "Point.h"

#include <vector>
#include <tuple>
#include <sstream>
#include <string>
#include <bits/stdc++.h>

Move::Move() {}

Move::Move(std::string sFromTerminal, bool isHex) {
	std::vector<std::string> splitInput = Operation::split(sFromTerminal," ");
	for (int i = 0; i < splitInput.size(); i+=3)
	{   
        std::string opc = splitInput[i];
        Operation::opcodeType opcNum;
        if (opc == "P") {
            opcNum = Operation::P;
        } else if (opc == "S") {
            opcNum = Operation::S;
        } else if (opc == "M") {
            opcNum = Operation::M;
        } else if (opc == "RS") {
            opcNum = Operation::RS;
        } else if (opc == "RE") {
            opcNum = Operation::RE;
        } else if (opc == "X") {
            opcNum = Operation::X;
        } else {
            throw std::invalid_argument("Invalid Opcode give to Move constructor");
        }
        
        try
        {   
            std::tuple<int, int> gotTuple = std::make_tuple(
            std::stoi(splitInput[i+1]),std::stoi(splitInput[i+2]));

            std::tuple<int, int> toPushTuple;
            if (isHex) {
                toPushTuple = Point::conversionToTriLinearCoord(gotTuple);
            } else {
                toPushTuple = gotTuple;
            }

            operationSequence.push_back(Operation(opcNum, toPushTuple));
        }
        catch(std::out_of_range)
        {
            throw std::invalid_argument("operationSequence length wrong in Move constructor");
        }
	}
}

Move::Move(std::vector<Operation> operationSeq) {
    operationSequence = operationSeq;
}

bool Move::operator ==(const Move& other) {
    if (operationSequence.size() != other.operationSequence.size()) {
        return false;
    }
    for (int i=0; i<operationSequence.size(); i++) {
        if (!(operationSequence[i] == other.operationSequence[i])) {
            return false;
        }
    }
    return true;
}

void Move::append(Move& secondMove) {
    if (operationSequence.size() != 0) {
        if (secondMove.operationSequence.size() != 0) {
            operationSequence.insert(operationSequence.end(), 
            secondMove.operationSequence.begin(), secondMove.operationSequence.end());
        }
    } else {
        if (secondMove.operationSequence.size() != 0) {
            operationSequence = secondMove.operationSequence;
        }
    }
}

std::string Move::toStr(bool isHex) {
    std::stringstream ss;
    for (int i = 0; i < operationSequence.size(); i++) {
        Operation op = operationSequence[i];
        if (op.opcode == Operation::P) {
            ss << "P ";
        } else if (op.opcode == Operation::S) {
            ss << "S ";
        } else if (op.opcode == Operation::M) {
            ss << "M ";
        } else if (op.opcode == Operation::RS) {
            ss << "RS ";
        } else if (op.opcode == Operation::RE) {
            ss << "RE ";
        } else if (op.opcode == Operation::X) {
            ss << "X ";
        }

        std::tuple<int, int> coordinateToPrint;
        if (isHex) {
            coordinateToPrint = Point::conversionToHexCoord(op.coordinate);
        } else {
            coordinateToPrint = op.coordinate;
        }

        ss << std::to_string(std::get<0>(coordinateToPrint)) << " " 
        << std::to_string(std::get<1>(coordinateToPrint));

        if (i == operationSequence.size()-1) {
            ss << std::endl;
        } else {
            ss << " ";
        } 
    }
    return ss.str();
}
