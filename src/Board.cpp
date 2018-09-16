#include "Board.h"
#include "Point.h"

#include <vector>
#include <tuple>

Board::Board(int boardSize) {
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
    }
}