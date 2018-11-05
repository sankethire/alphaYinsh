#Compiler
# we dont want other compiler to be used yet.
CXX = g++

#Flags
# CXX_LINKER_FLAGS

# Remove warning and add -Wall Flag
CXX_ASSEMBLER_FLAGS := -std=c++11 $(ADD_G++_FLAGS)

# Directories
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin

PARENT_DIR := $(OBJ_DIR)

AI_DIR := $(PARENT_DIR)/AI
GAME_DIR := $(PARENT_DIR)/Game

FILE_EXT := o

OUT_DIR = $(AI_DIR) $(GAME_DIR) $(BIN_DIR)
# Prereqs
AI_REQ := $(AI_DIR)/Ai.$(FILE_EXT) $(AI_DIR)/Tree.$(FILE_EXT) $(AI_DIR)/Huerisitic.$(FILE_EXT) $(AI_DIR)/Node.$(FILE_EXT)
GAME_REQ := $(GAME_DIR)/Game.$(FILE_EXT) $(GAME_DIR)/Board.$(FILE_EXT) $(GAME_DIR)/Player.$(FILE_EXT) $(GAME_DIR)/Move.$(FILE_EXT) $(GAME_DIR)/Operation.$(FILE_EXT) $(GAME_DIR)/Point.$(FILE_EXT)

.PHONY: all
all:
	make directories;
	make $(BIN_DIR)/ai;

.PHONY: directories
directories:
	mkdir -p $(OUT_DIR)

# BIN/Executable Rules
$(BIN_DIR)/ai: $(AI_REQ) $(GAME_REQ)
	$(CXX) $^ -o $@

$(BIN_DIR)/game: $(GAME_REQ)
	$(CXX) $^ -o $@

# OBJ/object Rules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXX_ASSEMBLER_FLAGS) -c $^ -o $@

.PHONY: clean
clean:
	rm -rf $(OUT_DIR)
