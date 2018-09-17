
int main()
{
	std::string cmd;
	std::getline(std::cin,cmd);
	Move move = Move(cmd);
	std::vector<Operation> os = move.operationSequence;
	std::cout<< move.toStr();
	return 0;
}
