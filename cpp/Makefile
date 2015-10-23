CXX = clang++
CXXFLAGS = -std=c++14 -Wall -Wextra -Werror
LIBS = -lm

all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))

%.out : %.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -o $@ $<
