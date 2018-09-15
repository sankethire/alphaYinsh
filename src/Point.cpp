#include "Point.h"

Point::Point(pieceType p, colorType c) {
    piece = p;
    color = c;
}


std::tuple<int, int> Point:: conversionToTriLinearCoord(std::tuple<int, int> hexCoord){
    std::vector<std::tuple<int,int>> coordinate_vector;
    std::tuple<int,int> vertex;
    std::tuple<int,int> triLinear_vector;
    if(std::get<0>(hexCoord)==0 && std::get<1>(hexCoord)==0 ){
        triLinear_vector = std::make_tuple(0,0);
        return triLinear_vector;
    }

    vertex = std::make_tuple(0,1);
    coordinate_vector.push_back(vertex);
    vertex = std::make_tuple(1,1);
    coordinate_vector.push_back(vertex);
    vertex = std::make_tuple(1,0);
    coordinate_vector.push_back(vertex);
    vertex = std::make_tuple(0,-1);
    coordinate_vector.push_back(vertex);
    vertex = std::make_tuple(-1,-1);
    coordinate_vector.push_back(vertex);
    vertex = std::make_tuple(-1,0);
    coordinate_vector.push_back(vertex);

    int cornerNum = std::get<1>(hexCoord) / std::get<0>(hexCoord);
    // std::cout << cornerNum << std::endl;
    std::tuple<int, int> cornerDirection = coordinate_vector[cornerNum];
    triLinear_vector = std::make_tuple(std::get<0>(hexCoord) * std::get<0>(cornerDirection),std::get<0>(hexCoord) * std::get<1>(cornerDirection));
    // std::cout << std::get<0>(triLinear_vector) << ", " << std::get<1>(triLinear_vector)<< std::endl;
    
    int mod = std::get<1>(hexCoord) % std::get<0>(hexCoord);
    // std::cout << mod << std::endl;

    std::tuple<int, int> sideDirection = coordinate_vector[(cornerNum+2)%6];
    // std::cout << std::get<0>(triLinear_vector) << ", " << std::get<1>(triLinear_vector)<< std::endl;
    int x = std::get<0>(triLinear_vector) + (mod * std::get<0>(sideDirection));
    int y = std::get<1>(triLinear_vector) + (mod * std::get<1>(sideDirection));
    triLinear_vector = std::make_tuple(x, y);
    return triLinear_vector;
}

