.PHONY: all clean run
CC = g++
CFLAGS = -std=c++11 -Wall
OPTFLAGS = -O3
LDFLAGS = -lm

SRC_DIR = src/
INC_DIR = inc/
BIN_DIR = bin/
OBJ_DIR = build/

EXEC = cb
INC = -I$(INC_DIR)
SRC = $(wildcard $(SRC_DIR)*.cpp)
OBJ = $(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)

.PHONY: all clean

all: directories $(EXEC)

directories: $(OBJ_DIR) $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

cb: $(OBJ)
	$(CC) $(CFLAGS) $(OPTFLAGS) $(LDFLAGS) $^ -o $(BIN_DIR)cb

# # test: $(filter-out $(OBJ_DIR)train_and_test.o, $(filter-out $(OBJ_DIR)train.o, $(OBJ)))
# 	$(CXX) $(CFLAGS) $(OPTFLAGS) $(LDFLAGS) $^ -o $(BIN_DIR)test

# train_and_test: $(filter-out $(OBJ_DIR)train.o, $(filter-out $(OBJ_DIR)test.o, $(OBJ)))
# 	$(CXX) $(CFLAGS) $(OPTFLAGS) $(LDFLAGS) $^ -o $(BIN_DIR)train_and_test

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@echo "$(SRC)"
	@echo "$(OBJ)"
	@echo ">> Compiling $<"
	$(CC) $(CFLAGS) $(OPTFLAGS) $(INC) -c $< -o $@

clean:a
	rm -rf $(OBJ_DIR) $(BIN_DIR)