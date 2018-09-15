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
    // tri linear coordinate of point. point knows where it is and 
    // its coordinates will never change
    std::tuple<int, int> triLinearCoord;

    /* FUNCTIONS */

    Point(pieceType p, colorType c);

    // convert hexagon coordinates to triLinear coordinates and vice versa
    std::tuple<int, int> conversionToTriLinearCoord(std::tuple<int, int> hexCoord);
    std::tuple<int, int> conversionToHexCoord(std::tuple<int, int> triCoord);
};

#endif /* POINT_H */