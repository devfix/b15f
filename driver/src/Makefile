# Name: Makefile
# Project: B15F (board15 Famulus Edition)
# Author: Tristan Krause
# Creation Date: 2019-03-22

# Environment
COMPILER_PATH = g++

# Options
LIB_DRV = ../lib/libb15fdrv.so
LIB_PATH = /usr/lib/
INCLUDE_PATH = /usr/include/b15f
OBJ_MAIN = main.o
OUT_CLI  = ../bin/cli.elf
OBJ_CLI  = cli.o
CFLAGS   = -std=c++17 -O3 -Wall -Wextra -fPIC
LDFLAGS_DRV  = -lcurses -lpthread
LDFLAGS  = $(LDFLAGS_DRV) -lb15fdrv
OBJECTS_DRV  = drv/usart.o drv/b15f.o drv/plottyfile.o drv/dot.o
OBJECTS_UI   = ui/view.o ui/view_selection.o ui/view_promt.o ui/view_info.o ui/view_monitor.o ui/ui.o

COMPILE = $(COMPILER_PATH) $(CFLAGS)

all: drv cli

drv: $(OBJECTS_DRV) $(LIB_DRV)
	

cli: drv $(OBJECTS_UI) $(OBJ_CLI)
	@echo "Linking cli..."
	mkdir -p ../bin
	$(COMPILE) $(OBJ_CLI) $(OBJECTS_UI) -L../lib -Wl,-rpath=../lib -o $(OUT_CLI) $(LDFLAGS)

install: drv
	cp $(LIB_DRV) $(LIB_PATH)
	mkdir -p $(INCLUDE_PATH)
	cp drv/*.h $(INCLUDE_PATH)
	
help:
	@echo "This Makefile compiles the b15f driver lib and command line interface (CLI):"
	@echo "make ......... to compile all"
	@echo "make drv ..... to compile the b15f driver lib"
	@echo "make cli ..... to compile the cli"
	@echo "make install . to install the lib and headers on this machine"
	@echo "make clean ... to delete objects and executables"
	
clean:
	@echo "Cleaning..."
	rm -f $(OBJECTS_DRV) $(OBJECTS_UI) $(OBJ_CLI) $(OUT_CLI) $(OBJ_MAIN) $(LIB_DRV)

.cpp.o:
	$(COMPILE) -c $< -o $@

$(LIB_DRV):
	@echo "Linking driver library..."
	mkdir -p ../lib
	$(COMPILE) $(OBJECTS_DRV) -shared -o $(LIB_DRV) $(LDFLAGS_DRV)
