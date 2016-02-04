# Cirion Makefile
# le 19 Décembre 2015
# par Jérémy S. "Qwoak" <qwoak11@gmail.com>

# Ràz
_OS		= 
_ARCH	=

# Cible par défaut.
ifeq ($(TARGET),)
	TARGET = debug
endif

# Windows
ifeq ($(OS),Windows_NT)
	_OS = Windows

	# x86 32-Bits
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		_ARCH = x86
	# x86 64-Bits
	else ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		_ARCH = x86_64
	endif

# Unix ?
else
	UNAME_S	= $(shell uname -s)
	ARCH 	= $(shell getconf LONG_BIT)

	# Mac OS X, OSX ou comme vous voulez
	ifeq ($(UNAME_S),Darwin)
		_OS = MacOSX

		# x86 64-Bits
		ifeq ($(ARCH),64)
			_ARCH = x86_64
		endif

	# Nunux
	else ifeq ($(UNAME_S),Linux)
		_OS = Linux

		# x86 32-Bits
		ifeq ($(ARCH),32)
			_ARCH = x86
		# x86 64-Bits
		else ifeq ($(ARCH),64)
			_ARCH = x86_64
		endif
	endif
endif

# OS O.K ?
ifeq ($(_OS),)
    $(error This project is not designed for this operating system ("-_-))
endif

# Arch O.K ?
ifeq ($(_ARCH),)
    $(error This project is not designed for the current architecture ("-_-))
endif

# Cible O.K ?
ifeq ($(TARGET),debug)
	#O.K.
else ifeq ($(TARGET),release)
	#O.K.
else
    $(error Invalid target.)
endif

# Définition des chemins.
SRC   = ./src
INC   = ./include
LIB   = ./lib/$(_OS)_$(_ARCH)
OBJ   = ./obj/$(_OS)_$(_ARCH)_$(TARGET)
BUILD = ./build/$(_OS)_$(_ARCH)_$(TARGET)

# Inclusions des chemins à scanner par le compilateur et l'éditeur de lien.
CCFLAGS = -I$(INC)
LDFLAGS = -L$(LIB)

# Inclusion de la configuration spécifique à l'OS.
# (Définition de OUT, CC, de la recette build, Màjs de CCFLAGS et LDFLAGS)
include ./mk/$(_OS).mk

# Recettes communes.
.PHONY: setup
.PHONY: clean
.PHONY: doc
.PHONY: timestamp

setup:
	mkdir -p $(OBJ) > /dev/null
	mkdir -p $(BUILD) > /dev/null
	mkdir -p $(LIB) > /dev/null

clean:
	rm $(BUILD)/$(OUT) > /dev/null
	rm $(OBJ)/*.o > /dev/null

doc:
	doxygen Doxyfile

timestamp:
	date +"%c" > TIMESTAMP
