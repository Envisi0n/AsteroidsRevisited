#
# Makefile for Asteroids
#

SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OTHER = -static-libgcc -static-libstdc++
EXECS = test.exe test

SHELL = sh
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)

all: linux

endif

ifeq ($(UNAME), MINGW32_NT-6.1)

all: mingw

endif

windows: CPP=i686-w64-mingw32-g++
windows: CPPFLAGS = -O0 -Wall -L SFML/lib -I SFML/include 
windows: test.exe

mingw: CPP=g++
mingw: CPPFLAGS = -O0 -g3 -Wall -L SFML/lib -I SFML/include 
mingw: test.exe

linux: CPP=g++
linux: CPPFLAGS = -O0 -g3 -Wall
linux: test

test.exe: test.cpp
	$(CPP) $(CPPFLAGS) -o test.exe test.cpp $(SFMLFLAGS) $(OTHER)

test: test.cpp
	$(CPP) $(CPPFLAGS) -o test test.cpp $(SFMLFLAGS) $(OTHER)

clean:
	rm -rf $(EXECS)
