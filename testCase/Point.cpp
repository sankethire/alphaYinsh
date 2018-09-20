
// Function check for Point::getTriLinearDirection()
 
int main(){
    // Game game = Game(5);
    Point::defineTriLinearDirection();
    std::tuple<int, int> tup  = Point::getTriLinearDirection(std::make_tuple(-5,-5),std::make_tuple(6,6));
    std::cout << std::get<0>(tup) << "," << std::get<1>(tup) << std::endl;
    
    return 0;
}
