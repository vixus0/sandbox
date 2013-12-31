CC=g++
CFLAGS=-Wall
LDFLAGS=-lsfml-window -lsfml-graphics -lsfml-system -lBox2D -lm

%.exe: %.cpp
	g++ -o $@ $< $(CFLAGS) $(LDFLAGS)

