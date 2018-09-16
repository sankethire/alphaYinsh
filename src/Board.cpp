#include "Board.h"
#include "Point.h"

#include <vector>
#include <tuple>
#include <iostream>
#include <sstream>

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
        //FIXME: COULD POSSIBLY REMOVE THIS LATER.
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

// FIXME: BEWARE HARD CODE AHEAD!
std::string Board::getColoredPoint(int x, int y) {
    return Board::getPointTriLinear(std::make_tuple(x, y)).Point::toColoredStringPoint();
}

// TODO: add possible moves option
std::string Board::toStringBoard() {
    std::stringstream strstream;
    strstream << "   " << "     " << " " << "     " << " " << " " << std::endl;
    strstream << " " << "     " << " " << "     " << getColoredPoint(-1,4) << "     " << getColoredPoint(1,5) << std::endl;
    strstream << "   " << "     " << " " << getColoredPoint(-2,3) << "     " << getColoredPoint(0,4) << "     " << getColoredPoint(2,5) << std::endl;
    strstream << " " << "     " << getColoredPoint(-3,2) << "     " << getColoredPoint(-1,3) << "     " << getColoredPoint(1,4) << "     " << getColoredPoint(3,5) << std::endl;
    strstream << "   " << getColoredPoint(-4,1) << "     " << getColoredPoint(-2,2) << "     " << getColoredPoint(0,3) << "     " << getColoredPoint(2,4) << "     " << getColoredPoint(4,5) << std::endl;
    strstream << " " << "     " << getColoredPoint(-3,1) << "     " << getColoredPoint(-1,2) << "     " << getColoredPoint(1,3) << "     " << getColoredPoint(3,4) << "     " << " " << std::endl;
    strstream << "   " << getColoredPoint(-4,0) << "     " << getColoredPoint(-2,1) << "     " << getColoredPoint(0,2) << "     " << getColoredPoint(2,3) << "     " << getColoredPoint(4,4) << std::endl;
    strstream << getColoredPoint(-5,-1) << "     " << getColoredPoint(-3,0) << "     " << getColoredPoint(-1,1) << "     " << getColoredPoint(1,2) << "     " << getColoredPoint(3,3) << "     " << getColoredPoint(5,4) << std::endl;
    strstream << "   " << getColoredPoint(-4,-1) << "     " << getColoredPoint(-2,0) << "     " << getColoredPoint(0,1) << "     " << getColoredPoint(2,2) << "     " << getColoredPoint(4,3) << std::endl;
    strstream << getColoredPoint(-5,-2) << "     " << getColoredPoint(-3,-1) << "     " << getColoredPoint(-1,0) << "     " << getColoredPoint(1,1) << "     " << getColoredPoint(3,2) << "     " << getColoredPoint(5,3) << std::endl;
    strstream << "   " << getColoredPoint(-4,-2) << "     " << getColoredPoint(-2,-1) << "     " << getColoredPoint(0,0) << "     " << getColoredPoint(2,1) << "     " << getColoredPoint(4,2) << std::endl;
    strstream << getColoredPoint(-5,-3) << "     " << getColoredPoint(-3,-2) << "     " << getColoredPoint(-1,-1) << "     " << getColoredPoint(1,0) << "     " << getColoredPoint(3,1) << "     " << getColoredPoint(5,2) << std::endl;
    strstream << "   " << getColoredPoint(-4,-3) << "     " << getColoredPoint(-2,-2) << "     " << getColoredPoint(0,-1) << "     " << getColoredPoint(2,0) << "     " << getColoredPoint(4,1) << std::endl;
    strstream << getColoredPoint(-5,-4) << "     " << getColoredPoint(-3,-3) << "     " << getColoredPoint(-1,-2) << "     " << getColoredPoint(1,-1) << "     " << getColoredPoint(3,0) << "     " << getColoredPoint(5,1) << std::endl;
    strstream << "   " << getColoredPoint(-4,-4) << "     " << getColoredPoint(-2,-3) << "     " << getColoredPoint(0,-2) << "     " << getColoredPoint(2,-1) << "     " << getColoredPoint(4,0) << std::endl;
    strstream << " " << "     " << getColoredPoint(-3,-4) << "     " << getColoredPoint(-1,-3) << "     " << getColoredPoint(1,-2) << "     " << getColoredPoint(3,-1) << "     " << " " << std::endl;
    strstream << "   " << getColoredPoint(-4,-5) << "     " << getColoredPoint(-2,-4) << "     " << getColoredPoint(0,-3) << "     " << getColoredPoint(2,-2) << "     " << getColoredPoint(4,-1) << std::endl;
    strstream << " " << "     " << getColoredPoint(-3,-5) << "     " << getColoredPoint(-1,-4) << "     " << getColoredPoint(1,-3) << "     " << getColoredPoint(3,-2) << std::endl;
    strstream << "   " << " " << "     " << getColoredPoint(-2,-5) << "     " << getColoredPoint(0,-4) <<  "     " << getColoredPoint(2,-3) <<std::endl;
    strstream << " " << "     " << " " << "     " << getColoredPoint(-1,-5) << "     " << getColoredPoint(1,-4) << std::endl;
    strstream << "   " << "     " << " " << "     " << " " << " " << std::std::endl;
}