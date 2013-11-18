#
# Makefile for OpenGL project

# ----- Make Variables -----

OPTFLAGS  =   -O3
DEFINES   =
CXXFLAGS  =	-g $(OPTFLAGS) -Wall -Wextra -pedantic $(DEFINES) 
CXX	  =	g++
LDLIBS    =     -lGL -lglut -lGLEW
TARGETS   = 	triangle shader_utils

# ----- Make Rules -----

all:	$(TARGETS)

clean:
	rm -f $(TARGETS) *.o
.PHONY: all clean

# ------ Dependences (.cpp -> .o using default Makefile rule) -----

triangle.o: triangle.cpp shader_utils.h

shader_utils.o: shader_utils.cpp shader_utils.h
