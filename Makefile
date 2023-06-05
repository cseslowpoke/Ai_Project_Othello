CXX = g++-13
CXXFLAGS = $(shell pkg-config --cflags sdl2) -Wall -std=c++17
CXXLIBS = $(shell pkg-config --libs sdl2)

# SRC = $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp) $(wildcard */*/*/*.cpp)
OBJ = $(SRC:%.cpp=obj/%.o)
SRC = $(filter-out main.cpp noSDL_main.cpp, $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp) $(wildcard */*/*/*.cpp))
EXEC = main.o

# 兩個主程式的 .cpp 檔案
MAIN_SRC = main.cpp
NOSDL_MAIN_SRC = noSDL_main.cpp

# 兩個主程式的 .o 檔案
MAIN_OBJ = $(MAIN_SRC:%.cpp=obj/%.o)
NOSDL_MAIN_OBJ = $(NOSDL_MAIN_SRC:%.cpp=obj/%.o)

# 兩個執行檔的名稱
EXEC1= program1.o
EXEC2 = program2.o

all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJ) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(CXXLIBS)

$(EXEC2): $(OBJ) $(NOSDL_MAIN_OBJ)
	$(CXX) -Wall -o $@ $^

obj/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(CXXLIBS)

clean:
	rm -rf *.o 
	rm -rf obj

indent:
	@clang-format -i agent/*.hpp
	@clang-format -i agent/utils/*.hpp
	@clang-format -i utils/*.hpp
	@clang-format -i *.cpp