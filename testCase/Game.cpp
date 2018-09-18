int main(){
    Point::defineTrilinearDirection();
    Game game = Game(5); 

    std::tuple<int, int> p1 = std::make_tuple(1,4);
    game.board.setPointTriLinear(p1,Point::marker,Point::orange);
    std::tuple<int, int> p2 = std::make_tuple(2,4);
    game.board.setPointTriLinear(p2,Point::marker,Point::orange);
    std::tuple<int, int> p3 = std::make_tuple(3,4);
    game.board.setPointTriLinear(p3,Point::marker,Point::orange);
    std::tuple<int, int> p4 = std::make_tuple(4,4);
    game.board.setPointTriLinear(p4,Point::marker,Point::orange);
    std::tuple<int, int> p5 = std::make_tuple(5,4);
    game.board.setPointTriLinear(p5,Point::marker,Point::orange);

    std::vector<Move> rem_move = game.contiguousMarker(5);


    std::cout << game.board.Board::toStringBoard();

    for(int i=0; i< rem_move.size();i++){
        for(int j=0;j<rem_move[i].operationSequence.size();j++){
            std::cout << rem_move[i].operationSequence[j].opcode << " " 
            << std::get<0>(rem_move[i].operationSequence[j].coordinate) << " " 
            << std::get<1>(rem_move[i].operationSequence[j].coordinate) << std::endl;

        }
    }



    return 0;
}
