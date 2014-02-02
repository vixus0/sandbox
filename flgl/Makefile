CXX  = g++
CXXFLAGS = -ggdb -Wall -I.
FLTKFLAGS = $(shell fltk-config --cxxflags --ldflags --use-gl)

all: flgl.exe

flgl.exe: flgl.cpp
	$(CXX) -o $@ $< $(CXXFLAGS) $(FLTKFLAGS)

