# Cirion Makefile: Windows
# le 09 Novembre 2015
# par Jérémy S. "Qwoak" <qwoak11@gmail.com>

ifeq ($(PWD),)
    $(error This makefile is designed to be run under emulated environment.)
endif

# --- Configurations. ----------------------------------------------------------

# Configuration spécifique à l'OS
CC       = g++.exe
CCFLAGS += -Wall
LDFLAGS += -lmingw32 -ltinyxml2 -lSDL2main -lSDL2

# Configuration pour l'architecture x86 32-Bits
ifeq ($(_ARCH),x86)
	CCFLAGS	+=
	LDFLAGS +=
# Configuration pour l'architecture x86 64-Bits
else ifeq ($(_ARCH),x86_64)
	CCFLAGS	+=
	LDFLAGS +=
endif

# Configuration pour la cible 'debug'
ifeq ($(TARGET),debug)
	OUT      = cirion-d.exe
	CCFLAGS += -g3 -D DEBUG
	LDFLAGS +=
# Configuration pour la cible 'release'
else ifeq ($(TARGET),release)
	OUT      = cirion.exe
	CCFLAGS += -O3
	LDFLAGS += -s
endif

# Définition de la liste des objets à construire.
OBJS = \
	bubble.cpp.o \
	ciexception.cpp.o \
	cirion.cpp.o \
	cmf.cpp.o \
	config.cpp.o \
	demo.cpp.o \
	graphic.cpp.o \
	log.cpp.o \
	object.cpp.o \
	surface.cpp.o \
	texture.cpp.o \
	timer.cpp.o \
	world.cpp.o \
	xmlerror.cpp.o \
	icon.rc.o \
	versioninfo.rc.o

# --- Définition des recettes. -------------------------------------------------

.PHONY: all
.PHONY: clean
.PHONY: setup
.PHONY: build

all: setup build

setup:
	mkdir -p $(OBJ) > /dev/null
	mkdir -p $(BUILD) > /dev/null
	mkdir -p $(LIB) > /dev/null

clean:
	rm $(BUILD)/$(OUT) > /dev/null
	rm $(OBJ)/*.o > /dev/null
	
build: $(OBJS)
	$(CC) -o $(BUILD)/$(OUT) $(wildcard $(OBJ)/*.o) $(LDFLAGS)

%.cpp.o: $(SRC)/%.cpp
	$(CC) -o $(OBJ)/$@ -c $< $(CCFLAGS)

%.rc.o: ./rc/%.rc
	windres $< $(OBJ)/$@

doc:
	doxygen Doxyfile
