#include "Move.h"

#include <vector>
#include <tuple>
#include <sstream>
#include <bits/stdc++.h>

// std::vector<std::string> split(std::string str,std::string sep){
//     char* cstr=const_cast<char*>(str.c_str());
//     char* current;
//     std::vector<std::string> arr;
//     current=strtok(cstr,sep.c_str());
//     while(current!=NULL){
//         arr.push_back(current);
//         current=strtok(NULL,sep.c_str());
//     }
//     return arr;
// }

Move::Move(std::string sFromTerminal) {
	std::vector<std::string> splitInput = Operation::split(sFromTerminal," ");
	for (int i = 0; i < splitInput.size(); i=i+3)
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
        } else if (opc == "x") {
            opcNum = Operation::X;
        } else {
            throw std::invalid_argument("Invalid Opcode give to Move constructor");
        }
        
        try
        {
            operationSequence.push_back(Operation(opcNum, std::make_tuple(stoi(splitInput[i+1]),stoi(splitInput[i+2]))));
        }
        catch(std::out_of_range)
        {
            throw std::invalid_argument("operationSequence length wrong in Move constructor");
        }
	}
}

// std::string Move::toStr() {
//     std::
// }
