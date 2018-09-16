#ifndef POINT_H
#define POINT_H

#include <vector>
#include <tuple>


extern std::vector<std::tuple<int,int>> triLinearDirection;


class Point {
public:
    /* FIELDS */

    // nonExistent is the points in last hexagon that doesn't exist
    enum pieceType {ring, marker, emptyPiece, nonExistentPiece};
    enum colorType {white, black, emptyColor, nonExistentColor};

    pieceType piece;
    colorType color;
    // tri linear coordinate of point. point knows where it is and 
    // its coordinates will never change
    std::tuple<int, int> triLinearCoord;

    /* FUNCTIONS */

    Point(std::tuple<int, int> triLinearCoordinate);

    void setPointState(pieceType p, colorType c);

    // convert hexagon coordinates to triLinear coordinates and vice versa
    static std::tuple<int, int> conversionToTriLinearCoord(std::tuple<int, int> hexCoord);
    static std::tuple<int, int> conversionToHexCoord(std::tuple<int, int> triCoord);
};

void defineTrilinearDirection();

#endif /* POINT_H */