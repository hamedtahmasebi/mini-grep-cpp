CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++20 -I./include
DEBUG_FLAGS = -g -O0 -DDEBUG
PROD_FLAGS  = -O2
OUT_DIR = ./out
SRC_DIR = ./src
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OUT_DIR)/%.o,$(SOURCES))
DEBUG_TARGET = main_debug.exe
PROD_TARGET = main.exe

all: $(OUT_DIR)/$(PROD_TARGET) $(OUT_DIR)/$(DEBUG_TARGET)

compile_prod: $(OUT_DIR)/$(PROD_TARGET)
$(OUT_DIR)/$(PROD_TARGET): $(OBJECTS)
	$(CXX) $(PROD_FLAGS) $^ -o $@

$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) $(PROD_FLAGS) -c $< -o $@


compile_debug: $(OUT_DIR)/$(DEBUG_TARGET)
$(OUT_DIR)/$(DEBUG_TARGET): $(OBJECTS:.o=_debug.o)
	$(CXX) $(DEBUG_FLAGS) $^ -o $@

$(OUT_DIR)/%_debug.o: $(SRC_DIR)/%.cpp | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -c $< -o $@


clean:
	rm -f $(OUT_DIR)/*.o $(OUT_DIR)/*.exe
