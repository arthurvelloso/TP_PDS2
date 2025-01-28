#compiler and flags
CC = g++
CFLAGS = -Wall -g -Iinclude


#directories
SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include


#where are the source files and where object files are going
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
OBJS_NO_MAIN = $(filter-out $(OBJ_DIR)/main.o, $(OBJS))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/test_%.o, $(TEST_SRCS))
#the main executable's and test files target
TARGET = $(BIN_DIR)/games
TEST_TARGETS = $(patsubst $(TEST_DIR)/%.cpp, $(BIN_DIR)/%, $(TEST_SRCS))


#default target
all: $(TARGET)


#command to compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


#command to compile test object files
$(OBJ_DIR)/test_%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


#command to compile the main executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^


#build all tests
tests: $(TEST_TARGETS)


#pattern for individual test executables
$(BIN_DIR)/%: $(OBJ_DIR)/test_%.o $(OBJS_NO_MAIN)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^


#individual test targets
test_connect4: $(BIN_DIR)/connect4test
test_reversi: $(BIN_DIR)/reversitest
test_tictactoe: $(BIN_DIR)/tictactoetest



#clean object and executable files
clean: 
	rm -rf $(OBJ_DIR) $(BIN_DIR)


#rebuild (clean and compile again)
rebuild: clean all