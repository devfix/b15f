# Name: Makefile
# Project: B15F (board15 Famulus Edition)
# Author: Tristan Krause
# Creation Date: 2019-03-22

# Environment
COMPILER_PATH = g++

# Options
LIB_DRV = ../lib/libb15fdrv.so
OBJ_MAIN = main.o
OUT_CLI  = ../bin/cli.elf
OBJ_CLI  = cli.o
CFLAGS   = -std=c++17 -O3 -Wall -Wextra -fPIC
LDFLAGS  = -lcurses -lpthread
OBJECTS_DRV  = drv/usart.o drv/b15f.o drv/plottyfile.o drv/dot.o
OBJECTS_UI   = ui/view.o ui/view_selection.o ui/view_promt.o ui/view_info.o ui/view_monitor.o ui/ui.o

COMPILE = $(COMPILER_PATH) $(CFLAGS)

all: drv cli

drv: $(OBJECTS_DRV)
	@echo "Linking driver library..."
	mkdir -p ../lib
	$(COMPILE) $(OBJECTS_DRV) -shared -o $(LIB_DRV) $(LDFLAGS)

cli: drv $(OBJECTS_UI) $(OBJ_CLI)
	@echo "Linking cli..."
	mkdir -p ../bin
	$(COMPILE) $(OBJ_CLI) $(OBJECTS_UI) -L../lib -Wl,-rpath=../lib -lb15fdrv -o $(OUT_CLI) $(LDFLAGS)

help:
	@echo "This Makefile compiles the b15f driver lib and command line interface (CLI):"
	@echo "make ......... to compile all"
	@echo "make drv ..... to compile the b15f driver lib"
	@echo "make cli  .... to compile the cli"
	@echo "make clean ... to delete objects and executables"
	
clean:
	@echo "Cleaning..."
	rm -f $(OBJECTS_DRV) $(OBJECTS_UI) $(OBJ_CLI) $(OUT_CLI) $(OBJ_MAIN) $(LIB_DRV)

.cpp.o:
	$(COMPILE) -c $< -o $@
