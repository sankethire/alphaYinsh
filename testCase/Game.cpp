// contiguous markers check (Board print get set points)
int main(){
    Point::defineTrilinearDirection();
    Game game = Game(5); 

    std::tuple<int, int> p0 = std::make_tuple(0,4);
    game.board.setPointTriLinear(p0,Point::marker,Point::orange);
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

    // std::tuple<int, int> p0 = std::make_tuple(-2,-2);
    // game.board.setPointTriLinear(p0,Point::marker,Point::orange);
    // std::tuple<int, int> p1 = std::make_tuple(-1,-1);
    // game.board.setPointTriLinear(p1,Point::marker,Point::orange);
    // std::tuple<int, int> p2 = std::make_tuple(0,0);
    // game.board.setPointTriLinear(p2,Point::marker,Point::orange);
    // std::tuple<int, int> p3 = std::make_tuple(1,1);
    // game.board.setPointTriLinear(p3,Point::marker,Point::orange);
    // std::tuple<int, int> p4 = std::make_tuple(2,2);
    // game.board.setPointTriLinear(p4,Point::marker,Point::orange);
    // std::tuple<int, int> p5 = std::make_tuple(3,3);
    // game.board.setPointTriLinear(p5,Point::marker,Point::orange);

    p0 = std::make_tuple(-2,-2);
    game.board.setPointTriLinear(p0,Point::marker,Point::orange);
    p1 = std::make_tuple(-1,-1);
    game.board.setPointTriLinear(p1,Point::marker,Point::orange);
    p2 = std::make_tuple(0,0);
    game.board.setPointTriLinear(p2,Point::marker,Point::orange);
    p3 = std::make_tuple(1,1);
    game.board.setPointTriLinear(p3,Point::marker,Point::orange);
    p4 = std::make_tuple(2,2);
    game.board.setPointTriLinear(p4,Point::marker,Point::orange);
    // p5 = std::make_tuple(3,3);
    // game.board.setPointTriLinear(p5,Point::marker,Point::orange);

    std::vector<Move> rem_move = game.contiguousMarker(5, Game::orange);


    std::cout << game.board.Board::toStringBoard();

    for(int i=0; i< rem_move.size();i++){
        for(int j=0;j<rem_move[i].operationSequence.size();j++){
            std::cout << rem_move[i].operationSequence[j].opcode << ", " 
            << std::get<0>(rem_move[i].operationSequence[j].coordinate) << ", " 
            << std::get<1>(rem_move[i].operationSequence[j].coordinate) << std::endl;
        }
    }



    return 0;
}

// possibleMovements check (Player addRing)
int main(){
    Point::defineTrilinearDirection();
    Game game = Game(5);
    Player requiredPlayer = *(std::get<0>(game.playerTuple));

    std::tuple<int, int> p0 = std::make_tuple(0,4);
    game.board.setPointTriLinear(p0,Point::marker,Point::orange);
    std::tuple<int, int> p1 = std::make_tuple(1,4);
    game.board.setPointTriLinear(p1,Point::marker,Point::orange);
    std::tuple<int, int> p2 = std::make_tuple(2,4);
    game.board.setPointTriLinear(p2,Point::marker,Point::orange);
    std::tuple<int, int> p3 = std::make_tuple(3,4);
    game.board.setPointTriLinear(p3,Point::ring,Point::orange);
    requiredPlayer.addRing(3, 4);
    std::tuple<int, int> p4 = std::make_tuple(4,4);
    game.board.setPointTriLinear(p4,Point::ring,Point::orange);
    requiredPlayer.addRing(4, 4);
    std::tuple<int, int> p5 = std::make_tuple(5,4);
    game.board.setPointTriLinear(p5,Point::marker,Point::orange);

    p0 = std::make_tuple(-2,-2);
    game.board.setPointTriLinear(p0,Point::marker,Point::orange);
    p1 = std::make_tuple(-1,-1);
    game.board.setPointTriLinear(p1,Point::marker,Point::orange);
    p2 = std::make_tuple(0,0);
    game.board.setPointTriLinear(p2,Point::marker,Point::orange);
    p3 = std::make_tuple(1,1);
    game.board.setPointTriLinear(p3,Point::marker,Point::orange);
    p4 = std::make_tuple(2,2);
    game.board.setPointTriLinear(p4,Point::marker,Point::orange);
    // p5 = std::make_tuple(3,3);
    // game.board.setPointTriLinear(p5,Point::marker,Point::orange);

    std::cout << game.board.Board::toStringBoard();
    std::vector<std::vector<std::vector<Move>>> allPosMovements
    = game.possibleMovementAllRingAllDirection(requiredPlayer);

    int count;
    for (std::vector<std::vector<Move>> i: allPosMovements) {
        count = 0;
        for (std::vector<Move> j: i) {
            std::cout << std::get<0>(triLinearDirection[count]) << ", " 
            << std::get<1>(triLinearDirection[count]) << std::endl;
            for (Move k: j) {
                std::cout << k.toStr();
            }
            count++;
        }
    }
    return 0;
}