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
MKDIR :=
ifeq ($(OS),Windows_NT)
	RM += rmdir /s /q
	MKDIR += mkdir
else
	RM += rm -rf
	MKDIR += mkdir -p
endif

# Compilers
CXX  = g++ -std=c++17
CC   = gcc

# Flags
ALLEGRO_DIR = vendor/allegro5
LIBS =  -L"$(ALLEGRO_DIR)/lib" -L"$(ALLEGRO_DIR)/bin"
CXXINCS = -I"$(ALLEGRO_DIR)/include"
WINLDFLAGS= -lallegro -lallegro_main -lallegro_font -lallegro_audio -lallegro_primitives -lallegro_acodec -lallegro_image -lallegro_color
LDFLAGS=$(shell pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_audio-5 allegro_primitives-5 allegro_acodec-5 allegro_image-5 allegro_color-5 --libs --cflags)

TARGETNAME=Explosions

# OS specific settings
FLAGS:=
ifeq ($(OS),Windows_NT)
	FLAGS += $(WINLDFLAGS) $(CXXINCS) $(LIBS)
else
	FLAGS += $(LDFLAGS)
endif

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# using windows copy utility requires backslashes
# TODO: find OS-agnostic solution
DLL_DIR := vendor\allegro5\bin
DLL := $(wildcard $(DLL_DIR)/*.dll)

EXE := $(BIN_DIR)/Explosions
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)



CPPFLAGS := -Iinclude -MMD -MP
CFLAGS   := -Wall
LDFLAGS  := -Llib
LDLIBS   := -lm

.PHONY: all clean run

all: $(EXE)
ifeq ($(OS),Windows_NT)
	copy $(DLL_DIR)\*.dll $(BIN_DIR) > NUL
	@echo "Windows build complete"
else
	@echo "Linux build complete"
endif

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CXX)  $^ $(LDLIBS) -o $@ $(FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXINCS) -c $< -o $@ $(FLAGS)

$(BIN_DIR) $(OBJ_DIR):
	$(MKDIR) $@

clean:
	$(RM) $(BIN_DIR) $(OBJ_DIR)

run: all
	$(EXE)
