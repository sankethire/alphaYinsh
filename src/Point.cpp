#include "Point.h"
#include <tuple>
#include <vector>

Point::Point(pieceType p, colorType c) {
    piece = p;
    color = c;
}


std::tuple<int, int> Point:: conversionToTriLinearCoord(std::tuple<int, int> hexCoord){
    std::tuple<int,int> triLinear_vector;
    if(std::get<0>(hexCoord)==0 && std::get<1>(hexCoord)==0 ){
        triLinear_vector = std::make_tuple(0,0);
        return triLinear_vector;
    }

    int cornerNum = std::get<1>(hexCoord) / std::get<0>(hexCoord);
    // std::cout << cornerNum << std::endl;
    std::tuple<int, int> cornerDirection = triLinearDirection[cornerNum];
    triLinear_vector = std::make_tuple(std::get<0>(hexCoord) * std::get<0>(cornerDirection),std::get<0>(hexCoord) * std::get<1>(cornerDirection));
    // std::cout << std::get<0>(triLinear_vector) << ", " << std::get<1>(triLinear_vector)<< std::endl;
    
    int mod = std::get<1>(hexCoord) % std::get<0>(hexCoord);
    // std::cout << mod << std::endl;

    std::tuple<int, int> sideDirection = triLinearDirection[(cornerNum+2)%6];
    // std::cout << std::get<0>(triLinear_vector) << ", " << std::get<1>(triLinear_vector)<< std::endl;
    int x = std::get<0>(triLinear_vector) + (mod * std::get<0>(sideDirection));
    int y = std::get<1>(triLinear_vector) + (mod * std::get<1>(sideDirection));
    triLinear_vector = std::make_tuple(x, y);
    return triLinear_vector;
}

std::tuple<int, int> conversionToHexCoord(std::tuple<int, int> triCoord) {
    // Trilinear point in which hexant(kind of like quadrant).
    // hextant includes one of the axis/corner. Earlier corner in clockwise direction is included.
    // The one it includes is the number assingned to this variable
    int hexant;

    // extrant x, y of TriLinearCoord
    int triLinearCoord_X = std::get<0>(triCoord);
    int triLinearCoord_Y = std::get<1>(triCoord);

    // Case analysis for assigning hexant
    // First divide in four then 120, 60, 120, 60
    // Then divide each 120 into two 60s
    if (triLinearCoord_X>=0) {
        if (triLinearCoord_Y>0) {
            // 1st 120
            // [0, +), (0, +)
            if (triLinearCoord_X < triLinearCoord_Y){
                hexant = 0;
            } else {
                hexant = 1;
            }
        } else {
            hexant = 2;
        }
    } else {
        if (triLinearCoord_Y>=0) {
            hexant = 5;
        } else {
            // 2nd 120
            // (-, 0), (-, 0] 
            if (triLinearCoord_X > triLinearCoord_Y){
                hexant = 3;
            } else {
                hexant = 4;
            }
        }
    }
    

}

void defineTrilinearDirection() {
    // Possibly call in game.cpp
    std::tuple<int,int> directionCorners;
    directionCorners = std::make_tuple(0,1);
    triLinearDirection.push_back(directionCorners);
    directionCorners = std::make_tuple(1,1);
    triLinearDirection.push_back(directionCorners);
    directionCorners = std::make_tuple(1,0);
    triLinearDirection.push_back(directionCorners);
    directionCorners = std::make_tuple(0,-1);
    triLinearDirection.push_back(directionCorners);
    directionCorners = std::make_tuple(-1,-1);
    triLinearDirection.push_back(directionCorners);
    directionCorners = std::make_tuple(-1,0);
    triLinearDirection.push_back(directionCorners);
}