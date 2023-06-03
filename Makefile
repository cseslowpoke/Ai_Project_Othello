CXX = g++-13
CXXFLAGS = $(shell pkg-config --cflags sdl2) -Wall 
CXXLIBS = $(shell pkg-config --libs sdl2)

all: main.cpp
	$(CXX) $(CXXFLAGS) -o main.o main.cpp $(CXXLIBS)
	@./main.o

clean:
	rm -rf *.o 

noSDL: noSDL_main.cpp
	$(CXX) $(CXXFLAGS) -o main.o noSDL_main.cpp $(CXXLIBS)
	@./main.o
indent:
	@clang-format -i agent/*.hpp
	@clang-format -i agent/utils/*.hpp
	@clang-format -i utils/*.hpp
	@clang-format -i *.cpp