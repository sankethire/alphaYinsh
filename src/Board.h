#ifndef BOARD_H
#define BOARD_H

#include "Point.h"

#include <vector>
#include <tuple>

class Board {
public:
    /* FIELDS */

    // 3 axes to denote 2D plane (ease of co-olinear access) David Peter coordinate system
    std::vector<std::vector<Point>> triLinearBoard;

    /* FUNCTIONS */

    Board(int boardSize);

    // gets the point
    // give cordinate x = [-boardSize, boardSize], y = [-boardSize, boardSize]
    // 5 ring game then boardSize = 5 
    Point getPointTriLinear(std::tuple<int, int> triLinearCoordinate);
};

#endif /* BOARD_H */