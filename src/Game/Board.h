#ifndef BOARD_H
#define BOARD_H

#include "Point.h"

#include <vector>
#include <tuple>
#include <string>

class Board {
public:
    /* FIELDS */
    int boardSize;

    // 3 axes to denote 2D plane (ease of co-olinear access) David Peter coordinate system
    std::vector<std::vector<Point>> triLinearBoard;

    /* FUNCTIONS */
    Board();
    Board(int size);

    // deep copy/clone
    Board clone();

    // gets the point
    // give cordinate x = [-boardSize, boardSize], y = [-boardSize, boardSize]
    // 5 ring game then boardSize = 5 
    Point& getPointTriLinear(std::tuple<int, int> triLinearCoordinate);
    Point& getPointTriLinear(int triLinearCoordX, int triLinearCoordY);


    void setPointTriLinear(std::tuple<int, int> triLinearCoordinate,
     Point::pieceType setPiece, Point::colorType setColor);
    void setPointTriLinear(int triLinearCoordX, int triLinearCoordY,
     Point::pieceType setPiece, Point::colorType setColor);

    // return string format of board to be printed in game.h
    // TODO: add possible moves option
    std::string getColoredPoint(int x, int y);
    std::string toStringBoard();
};

#endif /* BOARD_H */