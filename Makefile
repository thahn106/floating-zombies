# Project: Explosions
# Makefile created by Dev-C++ 4.9.9.2

CPP  = g++
CC   = gcc
RES  = 
OBJ  = MovableTest.o $(RES)
LINKOBJ  = MovableTest.o $(RES)
LIBS =  -L"$(CURDIR)" -mwindows lib/liballeg.a alld42.dll alleg42.dll allp42.dll allegro.h  
CXXINCS = -I"$(CURDIR)/allegro/include"
BIN  = Explosions.exe
CXXFLAGS = $(CXXINCS)
RM = rm -f


LDFLAGS=$(shell pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_audio-5 allegro_primitives-5 allegro_acodec-5 --libs --cflags)
OSXINC=/opt/homebrew/Cellar/allegro/5.2.9.1/include
OSXBIN=testbin
.PHONY: all all-before all-after clean clean-custom

all: all-before Explosions.exe all-after

test:
	@echo $(CXXINCS)

osx:
	g++ MovableTest.cpp -o "testbin" $(LDFLAGS)


clean: clean-custom
	${RM} $(OBJ) $(BIN) $(OSXBIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "Explosions.exe" $(LIBS)

MovableTest.o: MovableTest.cpp
	$(CPP) -c MovableTest.cpp -o MovableTest.o $(CXXFLAGS)
