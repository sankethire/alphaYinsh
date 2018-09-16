#include "Operation.h"

#include <string>
#include <bits/stdc++.h>

Operation::Operation(opcodeType opc, std::tuple<int, int> coord) {
    opcode = opc;
    coordinate = coord;
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
