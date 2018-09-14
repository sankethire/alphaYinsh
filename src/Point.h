#ifndef POINT_H
#define POINT_H

#include <vector>

class Point {
public:
    /* FIELDS */

    // nonExistent is the points in last hexagon that doesn't exist
    enum pieceType {ring, marker, empty, nonExistent};
    enum colorType {white, black, empty, nonExistent};

    pieceType piece;
    colorType color;

    // Immediate neighbours of a point
    std::vector<Point> crystalNeighbours;

    /* FUNCTIONS */

    Point(pieceType p, colorType c);
};

#endif /* POINT_H */