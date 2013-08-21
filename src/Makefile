#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

SHELL = sh
UNAME := $(shell uname)

# define the C compiler to use
CC = g++

# define any compile-time flags
CFLAGS = -Wall -g

# define any directories containing header files other than /usr/include
#

ifeq ($(UNAME), Linux)
#INCLUDES = -I SFGUI/include
else
INCLUDES = -I SFML/include
endif
# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
ifeq ($(UNAME), Linux)
#LFLAGS = -L SFGUI/lib
else
LFLAGS = -L SFML/lib
endif
# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system

# Other flags
OTHER = -static-libgcc -static-libstdc++

# define the C source files

# Client
CLIENT_SRCSRAW = $(foreach d,.,$(wildcard $(addprefix $(d)/game/*,.cpp)))
CLIENT_BIN = ./game/Asteroids.cpp
CLIENT_SRCS = $(filter-out $(CLIENT_BIN),$(CLIENT_SRCSRAW))

# Server
SERVER_SRCSRAW = $(foreach d,.,$(wildcard $(addprefix $(d)/server/*,.cpp)))
SERVER_BIN = ./server/AsteroidsServer.cpp
SERVER_SRCS = $(filter-out $(SERVER_BIN),$(SERVER_SRCSRAW))

# Shared
SHARED_SRCSRAW =  $(foreach d,.,$(wildcard $(addprefix $(d)/shared/*,.cpp)))
SHARED_FILTER =
SHARED_SRCS =  $(filter-out $(SHARED_FILTER),$(SHARED_SRCSRAW))

# Test executables
TESTS = testServer testClient

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
CLIENT_OBJS = $(CLIENT_SRCS:.cpp=.o)
SERVER_OBJS = $(SERVER_SRCS:.cpp=.o)
SHARED_OBJS = $(SHARED_SRCS:.cpp=.o)

# define the executable file
ifeq ($(UNAME), Linux)
CLIENT_MAIN = AsteroidsRevisited
SERVER_MAIN = AsteroidsRevisitedServer
else
CLIENT_MAIN = AsteroidsRevisited.exe
SERVER_MAIN = AsteroidsRevisitedServer.exe
endif

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all:    $(CLIENT_MAIN) $(SERVER_MAIN) install $(TESTS)
	@echo  Asteroids Build Successful

install: $(CLIENT_MAIN) $(SERVER_MAIN)
	cp $(CLIENT_MAIN) ../assets/ ; cp $(SERVER_MAIN) ../assets/

testServer: $(SERVER_OBJS) $(SHARED_OBJS) tests/testServer.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o testServer tests/testServer.cpp $(SERVER_OBJS) $(SHARED_OBJS) $(LFLAGS) $(LIBS) $(OTHER)
	
testClient: $(CLIENT_OBJS) $(SHARED_OBJS) tests/testClient.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o testClient tests/testClient.cpp $(CLIENT_OBJS) $(SHARED_OBJS) $(LFLAGS) $(LIBS) $(OTHER)

windows:   CC=i586-mingw32msvc-g++
windows:   INCLUDES = -I SFML/include
windows:   LFLAGS = -L SFML/lib
windows:   LIBS+= -lsfml-main
windows:   MAIN = AsteroidsRevisited.exe
windows: $(CLIENT_MAIN)
	@echo  Asteroids Build Successful

$(CLIENT_MAIN): $(CLIENT_OBJS) $(SHARED_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(CLIENT_MAIN) game/Asteroids.cpp $(CLIENT_OBJS) $(SHARED_OBJS) $(LFLAGS) $(LIBS) $(OTHER)

$(SERVER_MAIN): $(SERVER_OBJS) $(SHARED_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(SERVER_MAIN) server/AsteroidsServer.cpp $(SERVER_OBJS) $(SHARED_OBJS) $(LFLAGS) $(LIBS) $(OTHER)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) game/*.o server/*.o shared/*.o *~ ../assets/$(SERVER_MAIN) ../assets/$(CLIENT_MAIN) $(CLIENT_MAIN) $(SERVER_MAIN) testServer testClient

depend: $(SRCS) $(S_SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
