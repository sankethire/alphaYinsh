
int main(){
    Point::defineTrilinearDirection();
    Board board = Board(5);
    std::cout << board.toStringBoard();
    return 0;
}

int main(){
    Point::defineTrilinearDirection();
    Board board = Board(5);
    Board copyboard = board;
    std::tuple<int, int> p = std::make_tuple(4,2);
    board.setPointTriLinear(p,Point::ring,Point::orange);
    Point po = board.getPointTriLinear(p);
    std::cout << po.piece << " " << po.color << std::endl; 
    
    std::cout << board.toStringBoard();
    std::cout << std::endl;
    std::cout << copyboard.toStringBoard();
    return 0;
}
