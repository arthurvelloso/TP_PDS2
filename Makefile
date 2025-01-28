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
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_SRCS))
#the main executable's and test files target
TARGET = $(BIN_DIR)/games
TEST_TARGET = $(BIN_DIR)/test


#default target
all: $(TARGET)


#command to compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


#command to compile the executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^


#build tests
tests: $(TEST_TARGET)

$(TEST_TARGET): $(OBJS_NO_MAIN) $(TEST_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^


$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@



#clean object and executable files
clean: 
	rm -rf $(OBJ_DIR) $(BIN_DIR)


#rebuild (clean and compile again)
rebuild: clean all