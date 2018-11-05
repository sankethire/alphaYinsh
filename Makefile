# Directories
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin

OUT_DIR = $(OBJ_DIR) $(BIN_DIR)

AI_DIR = $(SRC_DIR)/AI
GAME_DIR = $(SRC_DIR)/Game

# Prereqs
AI_REQ = $(AI_DIR)/Ai.cpp $(AI_DIR)/Tree.cpp $(AI_DIR)/Huerisitic.cpp $(AI_DIR)/Node.cpp
GAME_REQ = $(GAME_DIR)/Game.cpp $(GAME_DIR)/Board.cpp $(GAME_DIR)/Player.cpp $(GAME_DIR)/Move.cpp $(GAME_DIR)/Operation.cpp $(GAME_DIR)/Point.cpp

.PHONY: all
all: $(AI_REQ) $(GAME_REQ)
	make directories;
	make $(BIN_DIR)/ai;

.PHONY: directories
directories:
	mkdir -p $(OUT_DIR)

$(BIN_DIR)/ai: $(AI_REQ) $(GAME_REQ)
	$(CXX) -Ofast $^ -o $@

$(BIN_DIR)/aiDebug: $(AI_REQ)
	$(CXX) -g $^ -o $@ 

$(BIN_DIR)/game: $(GAME_REQ)
	$(CXX) -Ofast $^ -o $@

$(BIN_DIR)/gameDebug: $(GAME_REQ)
	$(CXX) -g $^ -o $@

.PHONY: clean
clean:
	rm -rf $(OUT_DIR)
