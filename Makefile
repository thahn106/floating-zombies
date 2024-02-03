# Project: Explosions
# Makefile created by Dev-C++ 4.9.9.2

CPP  = g++.exe
CC   = gcc.exe
WINDRES = windres.exe
RES  = 
OBJ  = MovableTest.o $(RES)
LINKOBJ  = MovableTest.o $(RES)
LIBS =  -L"$(CURDIR)" -mwindows lib/liballeg.a alld42.dll alleg42.dll allp42.dll allegro.h  
CXXINCS = -I"$(CURDIR)/allegro/include"
BIN  = Explosions.exe
CXXFLAGS = $(CXXINCS)  
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before Explosions.exe all-after

test:
	@echo $(CXXINCS)


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "Explosions.exe" $(LIBS)

MovableTest.o: MovableTest.cpp
	$(CPP) -c MovableTest.cpp -o MovableTest.o $(CXXFLAGS)
