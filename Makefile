#compiler and flags
CC = g++
CFLAGS = -Wall -g -Iinclude


#directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include


#where are the source files and where object files are going
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
#the main executable's files target (which is also the default target)
TARGET = $(BIN_DIR)/games


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


#clean object and executable files
	rm -rf $(OBJ_DIR) $(BIN_DIR)


#rebuild (clean and compile again)
rebuild: clean all