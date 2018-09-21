
// Function check for Point::getTriLinearDirection()
 
int main(){
    // Game game = Game(5);
    Point::defineTriLinearDirection();
    std::tuple<int, int> tup  = Point::getTriLinearDirection(std::make_tuple(-5,-5),std::make_tuple(6,6));
    std::cout << std::get<0>(tup) << "," << std::get<1>(tup) << std::endl;
    
    return 0;
}

// David peter colors
std::string Point::toColoredStringPoint() {
    if (piece == Point::ring) {
        if (color == Point::orange) {
            return "\033[0;34mO\033[0m";
        } else if (color == Point::blue) {
            return "\033[0;32mO\033[0m";
        }
    } else if (piece == Point::marker) {
        if (color == Point::orange) {
            return "\033[0;44m.\033[0m";
        } else if (color == Point::blue) {
            return "\033[0;42m.\033[0m";
        }
    } else if (piece == Point::emptyPiece) {
        return "*";
    } else {
        return "";
    }
    std::stringstream ss;
    ss << std::to_string(piece) << ", " << std::to_string(color);
    return ss.str();
}
