#ifndef BOARD_H
#define BOARD_H

#include "Point.h"

#include <vector>
#include <tuple>

class Board {
public:
    /* FIELDS */
    int boardSize;

    // 3 axes to denote 2D plane (ease of co-olinear access) David Peter coordinate system
    std::vector<std::vector<Point>> triLinearBoard;

    /* FUNCTIONS */

    Board(int size);

    // gets the point
    // give cordinate x = [-boardSize, boardSize], y = [-boardSize, boardSize]
    // 5 ring game then boardSize = 5 
    Point getPointTriLinear(std::tuple<int, int> triLinearCoordinate);
    void setPointTriLinear(std::tuple<int, int> triLinearCoordinate,
     Point::pieceType setPiece,Point::colorType setColor);
};

#endif /* BOARD_H */