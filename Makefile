#
# Makefile for OpenGL project

# ----- Make Variables -----

OPTFLAGS  =   -O3
DEFINES   =
CXXFLAGS  =	-g $(OPTFLAGS) -Wall -Wextra -pedantic $(DEFINES) 
CXX	  =	g++
LDLIBS    =     -lglut -lGLEW -lGL
TARGETS   = 	test

# ----- Make Rules -----

all:	$(TARGETS)

clean:
	rm -f $(TARGETS) *.o

myspell: test.o
	$(CXX) $(CXXFLAGS) -o test test.o


# ------ Dependences (.cpp -> .o using default Makefile rule) -----

tests.o: test.cpp test.h

