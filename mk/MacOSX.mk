# Cirion Makefile: Mac OS X
# le 20 Décembre 2015
# par Jérémy S. "Qwoak"

# --- Configurations. ----------------------------------------------------------

# Configuration spécifique à l'OS
CC       = g++
CCFLAGS += -Wall
LDFLAGS += -ltinyxml2 -framework SDL2

# Configuration pour l'architecture x86 64-Bits
ifeq ($(_ARCH),x86_64)
	CCFLAGS +=
	LDFLAGS +=
endif

# Configuration pour la cible 'debug'
ifeq ($(TARGET),debug)
	OUT      = cirion-d
	CCFLAGS += -g3 -D DEBUG
	LDFLAGS +=
# Configuration pour la cible 'release'
else ifeq ($(TARGET),release)
	OUT      = cirion
	CCFLAGS += -O3
	LDFLAGS += -s
endif

# Définition de la liste des objets à construire.
OBJS = \
	ciexception.cpp.o \
	cirion.cpp.o \
	cmf.cpp.o \
	config.cpp.o \
	demo.cpp.o \
	entity.cpp.o \
	gameobject.cpp.o \
	graphic.cpp.o \
	hiro.cpp.o \
	introbubble.cpp.o \
	log.cpp.o \
	sprite.cpp.o \
	surface.cpp.o \
	texture.cpp.o \
	timer.cpp.o \
	world.cpp.o \
	xmlerror.cpp.o

# --- Définition des recettes. -------------------------------------------------

.PHONY: all
.PHONY: build

all: setup build
	
build: $(OBJS)
	$(CC) -o $(BUILD)/$(OUT) $(wildcard $(OBJ)/*.o) $(LDFLAGS)

%.cpp.o: $(SRC)/%.cpp
	$(CC) -o $(OBJ)/$@ -c $< $(CCFLAGS)
