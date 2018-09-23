
int main()
{
	std::string cmd;
	std::getline(std::cin,cmd);
	Move move = Move(cmd);
	std::vector<Operation> os = move.operationSequence;
	std::cout<< move.toStr();
	return 0;
}

// checking for move as hexCoord or triLinearCoord
int main(){
    Point::defineTriLinearDirection();
    std::string s;
    s = "P 1 2";
    Move move = Move(s,true);
    std::cout << move.toStr(false);

    s = "P 1 0";
    Move m = Move(s,false);
    std::cout << m.toStr(false);

    return 0;
}