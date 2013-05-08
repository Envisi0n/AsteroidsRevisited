#
# Makefile for Asteroids

SFMLFLAGS = -LSFML/lib -lsfml-graphics -lsfml-window -lsfml-system
OTHER = -static-libgcc -static-libstdc++
EXECS = test.exe

all: mingw

windows: CPP=i686-w64-mingw32-g++
windows: CPPFLAGS = -O0 -g3 -Wall -I SFML/include 
windows: test.exe

mingw: CPP=g++
mingw: CPPFLAGS = -O0 -g3 -Wall -I SFML/include 
mingw: test.exe


test.exe: test.cpp
	$(CPP) $(CPPFLAGS) -o test.exe test.cpp $(SFMLFLAGS) $(OTHER)
clean:
	rm -rf $(EXECS)
