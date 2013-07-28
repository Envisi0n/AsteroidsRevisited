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

# define the C source files

# Client
SRCSRAW = $(foreach d,.,$(wildcard $(addprefix $(d)/game/*,.cpp)))
BINS = ./game/Asteroids.cpp
SRCS = $(filter-out $(BINS),$(SRCSRAW))

# Server
S_SRCSRAW = $(foreach d,.,$(wildcard $(addprefix $(d)/server/*,.cpp)))
SBIN = ./server/AsteroidsServer.cpp
S_SRCS = $(filter-out $(SBIN),$(S_SRCSRAW))


# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.cpp=.o)
SOBJS = $(S_SRCS:.cpp=.o)

# define the executable file
ifeq ($(UNAME), Linux)
MAIN = AsteroidsRevisited
SMAIN = AsteroidsRevisitedServer
else
MAIN = AsteroidsRevisited.exe
SMAIN = AsteroidsRevisitedServer.exe
endif

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all:    $(MAIN) $(SMAIN) testServer testClient
	@echo  Asteroids Build Successful

install: $(MAIN)
	cp $(MAIN) ../assets/

testServer: $(SOBJS) tests/testServer.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o testServer tests/testServer.cpp $(SOBJS) $(LFLAGS) $(LIBS)
	
testClient: $(OBJS) tests/testClient.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o testClient tests/testClient.cpp $(OBJS) $(LFLAGS) $(LIBS)

windows:   CC=i586-mingw32msvc-g++
windows:   INCLUDES = -I SFML/include
windows:   LFLAGS = -L SFML/lib
windows:   LIBS+= -lsfml-main
windows:   MAIN = AsteroidsRevisited.exe
windows: $(MAIN)
	@echo  Asteroids Build Successful

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) game/Asteroids.cpp $(OBJS) $(LFLAGS) $(LIBS)

$(SMAIN): $(SOBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(SMAIN) server/AsteroidsServer.cpp $(SOBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) game/*.o *~ $(MAIN) $(SMAIN) testServer testClient

depend: $(SRCS) $(S_SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
