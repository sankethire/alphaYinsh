
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

int main()
{
    Point::defineTriLinearDirection();
    Board board = Board(5);
    std::cout << board.toStringBoard() << std::endl;

    board.setPointTriLinear(2,2,Point::ring,Point::orange);
    std::cout << board.toStringBoard() << std::endl;

    Board copy = board.clone();
    std::cout << copy.toStringBoard() << std::endl;

    copy.setPointTriLinear(3,3,Point::ring,Point::blue);
    std::cout << board.toStringBoard() << std::endl;
    std::cout << copy.toStringBoard() << std::endl;

    return 0;
}
