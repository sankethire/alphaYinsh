#ifndef BOARD_H
#define BOARD_H

#include "Point.h"

#include <vector>

class Board {
public:
    /* FIELDS */

    // 3 axes to denote 2D plane (ease of co-olinear access)
    std::vector<std::vector<std::vector<Point>>> triLinearBoard;

    /* FUNCTIONS */

    Board();
};

#endif /* BOARD_H */