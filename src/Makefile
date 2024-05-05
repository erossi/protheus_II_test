# Copyright (C) 2024 Enrico Rossi
#

export OPTLEV = 2
export MCU = atmega1284p
export FCPU = 8000000UL
export DMACRO = -D CBUF_SIZE=64 -D ISR_USART0_RX -D ISR_USART1_RX

PWD = $(shell pwd)
INCLUDE_DIR := $(PWD)/../include
LIB_DIR ?= $(PWD)/../lib

# Install dirs
export INSTALL_LIB := $(PWD)/../lib
export INSTALL_INCLUDE ?= $(PWD)/../include

# Compilers
CXX := avr-g++
BUILD_DIR ?= /run/user/$(shell id --user)/build
CXXFLAGS ?= -I$(INCLUDE_DIR) \
	    -Wall \
	    -Wextra \
	    -pedantic \
	    -std=c++14 \
	    -mmcu=$(MCU) \
	    -O$(OPTLEV) \
	    -fshort-enums \
	    $(DMACRO) \
	    -D F_CPU=$(FCPU)
LFLAGS = -L$(LIB_DIR) -lusart -lm
RM := rm -f

.PHONY: clean indent
.SILENT: help
.SUFFIXES: .cpp, .o

# set V=1 (eg, "make V=1") to print the full commands etc.
ifneq ($V,1)
 Pecho=@echo
 P=@
else
 Pecho=@:
 P=
endif

all: $(BUILD_DIR) lib $(INCLUDE_DIR) \
	test_10_echo

# Creates the object directory
$(BUILD_DIR):
	$P mkdir -p $(BUILD_DIR)

$(LIB_DIR):
	$P mkdir -p $(LIB_DIR)

$(INCLUDE_DIR):
	$P mkdir -p $(INCLUDE_DIR)

# Compile the usart lib, install the lib and the include
# files into ../lib and ../include directory.
libusart: $(LIB_DIR) $(INCLUDE_DIR)
	$(Pecho) "  BUILD libusart"
	$P cd ../modules/avrlib_cpp_usart/src && $(MAKE) install

lib: libusart

# List sources to be compiled always
common_o := AMB_usart.o

# Standard build
# WARN: positional argument are important
%.o: %.cpp
	$(Pecho) "  CXX   $<"
	$P $(CXX) -MMD -c $(CXXFLAGS) $< -o $(BUILD_DIR)/$@

test_%: $(common_o)
	$(Pecho) "  CXX   $@"
	$P $(CXX) $(CXXFLAGS) \
		$@.cpp $(addprefix $(BUILD_DIR)/, $(common_o)) \
		$(LFLAGS) \
		-o $(BUILD_DIR)/$@.elf

## CleanUp and tools
#
clean_libusart:
	$(Pecho) "  CLEAN libusart"
	$P cd ../modules/avrlib_cpp_usart/src && $(MAKE) clean

clean: clean_libusart
	$(Pecho) "  CLEAN"
	$P $(RM) $(BUILD_DIR)/test*
