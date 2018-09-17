
int main(){
    Point::defineTrilinearDirection();
    Board board = Board(5);
    std::cout << board.toStringBoard();
    return 0;
}

