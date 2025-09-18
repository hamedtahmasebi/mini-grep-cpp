CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++20 -I./include
OUT_DIR = ./out
SRC_DIR = ./src
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OUT_DIR)/%.o,$(SOURCES))
DEBUG_TARGET = main_debug.exe
PROD_TARGET = main.exe

all: $(OUT_DIR)/$(PROD_TARGET) $(OUT_DIR)/$(DEBUG_TARGET)

compile_prod: $(OUT_DIR)/$(PROD_TARGET)
$(OUT_DIR)/$(PROD_TARGET): $(OBJECTS)
	$(CXX) $^ -o $@

$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@



compile_debug: $(OUT_DIR)/$(DEBUG_TARGET)
$(OUT_DIR)/$(DEBUG_TARGET): $(OBJECTS:.o=_debug.o)
	$(CXX) $^ -o $@

$(OUT_DIR)/%_debug.o: $(SRC_DIR)/%.cpp | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -DDEBUG -c $< -o $@


clean:
	rm -f $(OUT_DIR)/*.o $(OUT_DIR)/*.exe
