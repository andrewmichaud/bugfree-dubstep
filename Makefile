#
# Makefile for OpenGL project

# ----- Make Variables -----

OPTFLAGS  =   -O3 -march=native
DEFINES   =
CXXFLAGS  =	-g $(OPTFLAGS) -Wall -Wextra -pedantic $(DEFINES) 
CXX	  =	g++
LDLIBS    =     -lGL -lglut -lGLEW -lm
TARGETS   = 	main

# ----- Make Rules -----

all:	$(TARGETS)

main: cube.o shader_utils.o
	$(CXX) -o $@ $^ $(LDLIBS)
clean:
	rm -f $(TARGETS) *.o

.PHONY: all clean

# Note: The three rules below use useful-but-cryptic make "Automatic variables"
#       to avoid duplicating information in multiple places, the most useful
#       of which are:
#
#   $@  The file name of the target of the rule  (e.g., stringhash-test below)
#   $^  The names of all the prerequisites, with spaces between them.
#       (e.g., stringhash-test.o stringhash.o)
#   $<  The name of the first prerequisite (e.g., stringhash-test.o); not used
#       in these rules, but sometimes useful
#
# See http://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
# ------ Dependences (.cpp -> .o using default Makefile rule) -----

cube.o: cube.cpp shader_utils.hpp

shader_utils.o: shader_utils.cpp shader_utils.hpp
