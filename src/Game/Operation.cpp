#include "Operation.h"

#include <string>
#include <bits/stdc++.h>

Operation::Operation(opcodeType opc, std::tuple<int, int> coord) {
    opcode = opc;
    coordinate = coord;
}

Operation::Operation(opcodeType opc, int coordX, int coordY) {
    opcode = opc;
    coordinate = std::make_tuple(coordX, coordY);
}

bool Operation::operator ==(const Operation& other) {
    if (opcode != other.opcode) {
        return false;
    }
    int this0 = std::get<0>(coordinate);
    int this1 = std::get<1>(coordinate);
    int other0 = std::get<0>(other.coordinate);
    int other1 = std::get<1>(other.coordinate);

    if (this0 != other0) {
        return false;
    }
    if (this1 != other1) {
        return false;
    }

    return true;
}

std::vector<std::string> Operation::split(std::string str,std::string sep){
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    std::vector<std::string> arr;
    current=std::strtok(cstr,sep.c_str());
    while(current!=NULL){
        arr.push_back(current);
        current=std::strtok(NULL,sep.c_str());
    }
    return arr;
}
