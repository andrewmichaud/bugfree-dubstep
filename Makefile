#
# Makefile for OpenGL project

# ----- Make Variables -----

OPTFLAGS  =   -O3
DEFINES   =
CXXFLAGS  =	-g $(OPTFLAGS) -Wall -Wextra -pedantic $(DEFINES) 
CXX	  =	g++
LDLIBS    =     -lGL -lglut -lGLEW -lm
TARGETS   = 	main

# ----- Make Rules -----

all:	$(TARGETS)

main: cube.o shader_utils.o
	$(CXX) -o main cube.cpp shader_utils.cpp $(LDLIBS)
clean:
	rm -f $(TARGETS) *.o

.PHONY: all clean

# ------ Dependences (.cpp -> .o using default Makefile rule) -----

cube.o: cube.cpp shader_utils.h

shader_utils.o: shader_utils.cpp shader_utils.h
