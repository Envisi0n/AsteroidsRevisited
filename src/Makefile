#
# Makefile for Asteroids
#

SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system
OTHER = -static-libgcc -static-libstdc++
EXECS = test.exe test testClient testServer
OBJS = Client.o Server.o

SHELL = sh
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)

CPP=g++
CPPFLAGS = -O0 -g3 -Wall

all: linux

endif

ifeq ($(UNAME), MINGW32_NT-6.1)

all: mingw

endif

windows: CPP=i586-mingw32msvc-g++
windows: CPPFLAGS = -O0 -g3 -Wall -L SFML/lib -I SFML/include 
windows: test.exe

mingw: CPP=g++
mingw: CPPFLAGS = -O0 -g3 -Wall -L SFML/lib -I SFML/include 
mingw: test.exe

linux: CPP=g++
linux: CPPFLAGS = -O0 -g3 -Wall
linux: test

Client.o: Client.hpp Client.cpp
	$(CPP) $(CPPFLAGS) -c -o Client.o Client.cpp

Server.o: Server.hpp Server.cpp
	$(CPP) $(CPPFLAGS) -c -o Server.o Server.cpp

test.exe: test.cpp $(OBJS)
	$(CPP) $(CPPFLAGS) -o test.exe test.cpp $(OBJS) $(SFMLFLAGS) $(OTHER)

test: test.cpp $(OBJS)
	$(CPP) $(CPPFLAGS) -o test test.cpp $(OBJS) $(SFMLFLAGS) $(OTHER)


# Tests
testClient: Client.o testClient.cpp
	$(CPP) $(CPPFLAGS) -o testClient testClient.cpp Client.o $(SFMLFLAGS) $(OTHER)

testServer: Server.o testServer.cpp
	$(CPP) $(CPPFLAGS) -o testServer testServer.cpp Server.o $(SFMLFLAGS) $(OTHER)

clean:
	rm -rf $(EXECS) $(OBJS)
