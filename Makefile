# OS Detection
OSFLAG :=
ifeq ($(OS),Windows_NT)
	OSFLAG += -D WIN32
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		OSFLAG += -D AMD64
	endif
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		OSFLAG += -D IA32
	endif
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG += -D LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG += -D OSX
	endif
		UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		OSFLAG += -D AMD64
	endif
		ifneq ($(filter %86,$(UNAME_P)),)
	OSFLAG += -D IA32
		endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		OSFLAG += -D ARM
	endif
endif


# OS specific settings
RM :=
ifeq ($(OS),Windows_NT)
	RM += del /Q /F
else
	RM += rm -f
endif

# Compilers
CPP  = g++
CC   = gcc

RES  = 
OBJ  = MovableTest.o $(RES)
LINKOBJ  = MovableTest.o $(RES)

# Flags
ALLEGRO_DIR = $(CURDIR)/allegro5
LIBS =  -L"$(ALLEGRO_DIR)/lib" -L"$(ALLEGRO_DIR)/bin"
CXXINCS = -I"$(CURDIR)/allegro5/include"
WINLDFLAGS= -lallegro -lallegro_main -lallegro_font -lallegro_audio -lallegro_primitives -lallegro_acodec -lallegro_image -lallegro_color
LDFLAGS=$(shell pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_audio-5 allegro_primitives-5 allegro_acodec-5 allegro_image allegro_color --libs --cflags)

# Build targets
BUILDDIR=build
TARGETNAME=Explosions

# OS specific settings
TARGET:= 
FLAGS:=
ifeq ($(OS),Windows_NT)
	TARGET += $(BUILDDIR)\$(TARGETNAME).exe
	FLAGS += $(WINLDFLAGS) $(CXXINCS) $(LIBS)
else
	TARGET += $(BUILDDIR)/$(TARGETNAME)
	FLAGS += $(LDFLAGS)
endif

SOURCES :=
SOURCES += MovableTest.cpp
SOURCES += Background.cpp
SOURCES += Creature.cpp
SOURCES += Immovable.cpp
SOURCES += Movable.cpp
SOURCES += Player.cpp
SOURCES += Enemy.cpp

default: clean all

clean:
	${RM} $(OBJ) $(TARGET)

all:
	@echo Building $(TARGET) with $(OSFLAG)
	$(CPP) $(SOURCES) -o $(TARGET) $(FLAGS)

test:
	@echo Testing build settings with $(OSFLAG)
	@echo CPP: $(CPP)
	@echo TARGET: $(TARGET)
	@echo FLAGS: $(FLAGS)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "Explosions.exe" $(LIBS)

MovableTest.o: MovableTest.cpp
	$(CPP) -c MovableTest.cpp -o MovableTest.o $(CXXFLAGS)
