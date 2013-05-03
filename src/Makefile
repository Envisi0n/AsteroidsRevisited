#
# Makefile for Asteroids

SFMLFLAGS = -LSFML/lib -lsfml-graphics -lsfml-window -lsfml-system
OTHER = -static-libgcc -static-libstdc++
EXECS = test

all: mingw

mingw: CPP=g++
mingw: CPPFLAGS = -O0 -g3 -Wall -I SFML/include
mingw: test.exe


test.exe: test.cpp
	$(CPP) $(OTHER) $(CPPFLAGS) -o test.exe test.cpp $(SFMLFLAGS)
	
clean:
	rm -rf $(EXECS)