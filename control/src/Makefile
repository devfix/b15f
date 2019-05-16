# Name: Makefile
# Project: B15F (board15 Famulus Edition)
# Author: Tristan Krause
# Creation Date: 2019-03-22

# Environment
PATH_COMPILER = g++

# install paths
PATH_BIN     = /usr/bin/
PATH_LIB     = /usr/lib/
PATH_INCLUDE = /usr/include/b15f/

# tmp paths
PATH_TMP_BIN = ../bin/
PATH_TMP_LIB = ../lib/

# outputs
OUT_TMP_DRV = $(PATH_TMP_LIB)/libb15fdrv.so
OUT_TMP_CLI  = $(PATH_TMP_BIN)/cli.elf
OUT_DRV = $(PATH_LIB)/libb15fdrv.so

# compiling & linking parameters
CFLAGS   = -std=c++17 -O3 -Wall -Wextra -fPIC
LDFLAGS_DRV  = -lcurses -lpthread
LDFLAGS_CLI  = $(LDFLAGS_DRV) -lb15fdrv

# objects
OBJECTS_DRV  = drv/usart.o drv/b15f.o drv/plottyfile.o drv/dot.o
OBJECTS_CLI   = cli.o ui/view.o ui/view_selection.o ui/view_promt.o ui/view_info.o ui/view_monitor.o ui/ui.o



# *** TARGETS ***

all: drv cli

drv: $(OBJECTS_DRV) $(OUT_TMP_DRV)
	

cli: drv $(OBJECTS_CLI)
	@echo "Linking cli..."
	@mkdir -p ../bin
	$(PATH_COMPILER) $(CFLAGS) $(OBJECTS_CLI) -L $(PATH_TMP_LIB) -o $(OUT_TMP_CLI) $(LDFLAGS_CLI)
	@bash -c 'if [ ! -f "$(OUT_DRV)" ]; then echo -e "\n*** Warning ***: driver not installed\nType \"sudo make install\" to install or update b15fdrv."; fi'

install: drv
	@echo "Installing driver..."
	@mkdir -p $(PATH_INCLUDE)
	cp plotty $(PATH_BIN)
	cp $(OUT_TMP_DRV) $(PATH_LIB)
	cp drv/*.h $(PATH_INCLUDE)
	
help:
	@echo "This Makefile compiles the b15f driver lib and command line interface (CLI):"
	@echo "make ......... to compile all"
	@echo "make drv ..... to compile the b15f driver lib"
	@echo "make cli ..... to compile the cli"
	@echo "make install . to install the lib and headers on this machine"
	@echo "make clean ... to delete objects and executables"
	
clean:
	@echo "Cleaning..."
	rm -f $(OBJECTS_DRV) $(OBJECTS_CLI) $(OUT_TMP_CLI) $(OUT_TMP_DRV)

.cpp.o:
	$(PATH_COMPILER) $(CFLAGS) -c $< -o $@

$(OUT_TMP_DRV):
	@echo "Linking driver library..."
	@mkdir -p ../lib
	$(PATH_COMPILER) $(CFLAGS) $(OBJECTS_DRV) -shared -o $(OUT_TMP_DRV) $(LDFLAGS_CLI_DRV)
