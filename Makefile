#
# Makefile for OpenGL project

# ----- Make Variables -----

OPTFLAGS  =     -O3 -march=native
DEFINES   =
STD       =     -std=c++11
CXXFLAGS  =	-g $(STD) $(OPTFLAGS) -Wall -Wextra -pedantic $(DEFINES) 
CXX	  =	clang++
LDLIBS    =     -lSDLmain -lSDL -lSDL_image 
TARGETS   = 	bdPlatformer

# ----- Make Rules -----

all:	$(TARGETS)

bdPlatformer:   CApp.o CSurface.o CEvent.o CAnimation.o CEntity.o CArea.o \
    CMap.o CTile.o CCamera.o CFPS.o CPlayer.o
	$(CXX) -o $@ $^ $(LDLIBS)

native: 
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
# See http://www.gnu.org/software/make/manual/html_node/Automatic-Variables.hpptml
# ------ Dependences (.cpp -> .o using default Makefile rule) -----

CApp.o: CApp.cpp CApp.hpp CSurface.hpp CEvent.hpp CAnimation.hpp CEntity.hpp CArea.hpp \
    CMap.hpp CTile.hpp CCamera.hpp CFPS.hpp CPlayer.hpp Define.hpp

CSurface.o: CSurface.cpp CSurface.hpp

CEvent.o: CEvent.cpp CEvent.hpp

CAnimation.o: CAnimation.cpp CAnimation.hpp

CEntity.o: CEntity.cpp CEntity.hpp CAnimation.hpp CCamera.hpp CFPS.hpp CSurface.hpp \
    CArea.hpp

CArea.o: CArea.cpp CArea.hpp

CMap.o: CMap.cpp CMap.hpp

CTile.o: CTile.cpp CTile.hpp

CCamera.o: CCamera.cpp CCamera.hpp

CFPS.o: CFPS.cpp CFPS.hpp

CPlayer.o: CPlayer.cpp CPlayer.hpp CEntity.hpp
