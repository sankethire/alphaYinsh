#include "Board.h"
#include "Point.h"

#include <vector>
#include <tuple>
#include <iostream>

Board::Board(int size) {
    boardSize = size;
    for (int i=-boardSize; i<=boardSize; i++) {
        std::vector<Point> colomnVector;
        for (int j=-boardSize; j<=boardSize; j++) {
            Point p = Point::Point(std::make_tuple(i, j));
            std::tuple<int, int> hexCoord = Point::conversionToHexCoord(std::make_tuple(i, j));
            int hexagon = std::get<0>(hexCoord);
            int position = std::get<1>(hexCoord);
            if ((hexagon>boardSize) ||  ((hexagon==boardSize) && (position%hexagon==0))) {
                p.setPointState(Point::nonExistentPiece, Point::nonExistentColor);
            } else {
                p.setPointState(Point::emptyPiece, Point::emptyColor);
            }
            colomnVector.push_back(p);
        }
        triLinearBoard.push_back(colomnVector);
    }
}

Point Board::getPointTriLinear(std::tuple<int, int> triLinearCoordinate) {
    int triLinearCoordX = std::get<0>(triLinearCoordinate);
    int triLinearCoordY = std::get<1>(triLinearCoordinate);
    if ((-boardSize<=triLinearCoordX) && (triLinearCoordX<=boardSize) 
    && (-boardSize<=triLinearCoordY) && (triLinearCoordY<=boardSize)) {
        return  triLinearBoard[triLinearCoordX+boardSize][triLinearCoordY+boardSize];
    } else {
        // COULD POSSIBLY REMOVE THIS LATER.
        std::cerr << triLinearCoordX << ", " << triLinearCoordY << std::endl;
        throw std::invalid_argument("getPointTriLinear gets wrong coordinate");
    }
}

void Board::setPointTriLinear(std::tuple<int, int> triLinearCoordinate, 
Point::pieceType setPiece,Point::colorType setColor) {
    Point gotP = Board::getPointTriLinear(triLinearCoordinate);
    gotP.piece = setPiece;
    gotP.color = setColor;
}