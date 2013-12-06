#
# Makefile for OpenGL project

# ----- Make Variables -----

OPTFLAGS  =   -O3 -march=native
DEFINES   =
STD       =     -std=c++11
CXXFLAGS  =	-g $(STD) $(OPTFLAGS) -Wall -Wextra -pedantic $(DEFINES) 
CXX	  =	g++
LDLIBS    =     -lSDLmain -lSDL -lSDL_image 
TARGETS   = 	main

# ----- Make Rules -----

all:	$(TARGETS)

main:   CApp.o CSurface.o CEvent.o CAnimation.o CEntity.o CArea.o CMap.o CTile.o CCamera.o CFPS.o
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

CApp.o: CApp.cpp CApp.h CSurface.h CEvent.h CAnimation.h CEntity.h CArea.h CMap.h CTile.h CCamera.h CFPS.h Define.h

CSurface.o: CSurface.cpp CSurface.h

CEvent.o: CEvent.cpp CEvent.h

CAnimation.o: CAnimation.cpp CAnimation.h

CEntity.o: CEntity.cpp CEntity.h CAnimation.h CCamera.h CFPS.h CSurface.h

CArea.o: CArea.cpp CArea.h

CMap.o: CMap.cpp CMap.h

CTile.o: CTile.cpp CTile.h

CCamera.o: CCamera.cpp CCamera.h

CFPS.o: CFPS.cpp CFPS.h

