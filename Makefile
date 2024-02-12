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
CPPFLAGS := -Iinclude -MMD -MP
CFLAGS   := -Wall
CXXINCS  :=
CXXINCS  += -I"vendor/allegro5/include"
CXXINCS  += -I"vendor/"


LIBS       := -L"vendor/allegro5/lib"
LDLIBS     := -lm
WINLDFLAGS := -lallegro -lallegro_main -lallegro_font -lallegro_audio -lallegro_primitives -lallegro_acodec -lallegro_image -lallegro_color
LDFLAGS    := -Llib $(shell pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_audio-5 allegro_primitives-5 allegro_acodec-5 allegro_image-5 allegro_color-5 --libs --cflags)


TARGETNAME=GameLauncher

# OS specific settings
FLAGS =
MKDIR =
ifeq ($(OS),Windows_NT)
	FLAGS += $(WINLDFLAGS) $(LIBS)
	MKDIR += mkdir $(subst /,\,$@)
else
	FLAGS += $(LDFLAGS) $(LIBS)
	MKDIR += mkdir -p $@
endif

cc-compile = $(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXINCS) -c $< -o $@
cc-link    = $(CXX)  $^ $(LDLIBS) -o $@ $(FLAGS)

SRC_DIR := src
SRC_SUB_DIR := $(patsubst %/,%,$(sort $(dir $(wildcard src/*/))))
OBJ_DIR := obj
OBJ_SUB_DIR := $(addprefix $(OBJ_DIR)/, $(SRC_SUB_DIR:$(SRC_DIR)/%=%))
BIN_DIR := bin

# using windows copy utility requires backslashes
# TODO: find OS-agnostic solution
DLL_DIR := vendor\allegro5\bin
DLL := $(wildcard $(DLL_DIR)/*.dll)

EXE := $(BIN_DIR)/$(TARGETNAME)
SRC := $(wildcard $(SRC_DIR)/*.cpp)
SRC += $(wildcard $(SRC_DIR)/*/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

.PHONY: all clean run

all: $(EXE)
ifeq ($(OS),Windows_NT)
	copy $(DLL_DIR)\*.dll $(BIN_DIR) > NUL
	@echo "Windows build complete"
else
	@echo "Linux build complete"
endif

$(EXE): $(OBJ) | $(BIN_DIR)
	$(cc-link)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR) $(OBJ_SUB_DIR)
	$(cc-compile)

$(BIN_DIR) $(OBJ_DIR) $(OBJ_SUB_DIR):
	$(MKDIR)

clean:
	$(RM) $(BIN_DIR) $(OBJ_DIR)

run: all
	$(EXE)

test:
	@echo $(SRC_SUB_DIR)
	@echo $(OBJ_SUB_DIR)