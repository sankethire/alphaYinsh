#include "Point.h"
#include <tuple>
#include <vector>

Point::Point(pieceType p, colorType c) {
    piece = p;
    color = c;
}


std::tuple<int, int> Point::conversionToTriLinearCoord(std::tuple<int, int> hexCoord){
    std::tuple<int,int> triLinearCoord;
    if(std::get<0>(hexCoord)==0 && std::get<1>(hexCoord)==0 ){
        triLinearCoord = std::make_tuple(0,0);
        return triLinearCoord;
    }

    int cornerNum = std::get<1>(hexCoord) / std::get<0>(hexCoord);
    
    std::tuple<int, int> cornerDirection = triLinearDirection[cornerNum];
    // 0 + hexagon*cornerDirection
    triLinearCoord = std::make_tuple(std::get<0>(hexCoord) * std::get<0>(cornerDirection),std::get<0>(hexCoord) * std::get<1>(cornerDirection));
    
    
    int posModHex = std::get<1>(hexCoord) % std::get<0>(hexCoord);

    std::tuple<int, int> sideDirection = triLinearDirection[(cornerNum+2)%6];
    //  + (postion%hexagon)*sideDirection
    int triLinearCoordX = std::get<0>(triLinearCoord) + (posModHex * std::get<0>(sideDirection));
    int triLinearCoordY = std::get<1>(triLinearCoord) + (posModHex * std::get<1>(sideDirection));
    triLinearCoord = std::make_tuple(triLinearCoordX, triLinearCoordY);
    return triLinearCoord;
}

std::tuple<int, int> Point::conversionToHexCoord(std::tuple<int, int> triCoord) {
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

    // a*cornerDirection + b*sideDirection = triLinearCoord
    // hexagon = a, position = hexant*hexagon + b 
    // +2 to get sideDirection.
    std::tuple<int, int> sideDirection = triLinearDirection[(hexant+2)%6];
    std::tuple<int, int> cornerDirection = triLinearDirection[hexant];

    int sideDirection0 = std::get<0>(sideDirection);
    int sideDirection1 = std::get<1>(sideDirection);
    int cornerDirection0 = std::get<0>(cornerDirection);
    int cornerDirection1 = std::get<1>(cornerDirection);
    int triCoord0 = std::get<0>(triCoord);
    int triCoord1 = std::get<1>(triCoord);

    int hexagon, position;

    int coeffA = (triCoord1*sideDirection0 - triCoord0*sideDirection1)/
    (cornerDirection1*sideDirection0 - cornerDirection0*sideDirection1); 
    int coeffB = (triCoord1*cornerDirection0 - triCoord0*cornerDirection1)/
    (sideDirection1*cornerDirection0 - sideDirection0*cornerDirection1);

    hexagon = coeffA;
    position = hexant*hexagon + coeffB;
    return std::make_tuple(hexagon, position);
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