#ifndef OPERATION_H
#define OPERATION_H

#include <tuple>

class Operation {
public:
    /* FIELDS */
    enum OpcodeType {P, S, M, RS, RE, X};
    OpcodeType opcode;

    // Coordinates are triLinear
    std::tuple<int, int> coordinate;

    /* FUNCTIONS */
    Operation(OpcodeType opc);
};

#endif /* OPERATION_H */