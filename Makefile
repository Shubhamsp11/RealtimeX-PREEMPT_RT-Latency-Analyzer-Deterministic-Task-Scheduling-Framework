CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread
INCLUDES = -Iapp

SRC_DIR = app
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
TARGET = realtimex

all: directories $(TARGET)

debug: CXXFLAGS += -g -O0
debug: all

release: CXXFLAGS += -O3
release: all

directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p results

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET) results/*.log

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	./$(TARGET) < tests/demo_input.txt

kernel:
	$(MAKE) -C kernel

.PHONY: all clean run test kernel debug release directories
