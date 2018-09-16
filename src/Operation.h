#ifndef OPERATION_H
#define OPERATION_H

#include <tuple>
#include <vector>

class Operation {
public:
    /* FIELDS */
    enum opcodeType {P, S, M, RS, RE, X};
    opcodeType opcode;

    // Coordinates are triLinear
    std::tuple<int, int> coordinate;

    /* FUNCTIONS */
    Operation(opcodeType opc, std::tuple<int, int> coord);

    // split string to vector of string according to delimiter
    static std::vector<std::string> split(std::string str,std::string sep);
};

#endif /* OPERATION_H */