#ifndef POINT_H
#define POINT_H

#include <vector>
#include <tuple>

class Point {
public:
    /* FIELDS */

    // nonExistent is the points in last hexagon that doesn't exist
    enum pieceType {ring, marker, empty, nonExistent};
    enum colorType {white, black, empty, nonExistent};

    pieceType piece;
    colorType color;

    // // Immediate neighbours of a point
    // std::vector<Point> crystalNeighbours;

    /* FUNCTIONS */

    Point(pieceType p, colorType c);
    
    // convert hexagon coordinates to triLinear coordinates and vice versa
    std::tuple<int, int, int> conversionToTriLinearCoord(std::tuple<int, int> hexCoord);
    std::tuple<int, int> conversionToHexCoord(std::tuple<int, int, int> triCoord);
};

#endif /* POINT_H */