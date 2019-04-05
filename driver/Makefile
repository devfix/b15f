# Name: Makefile
# Project: B15F (board15 Famulus Edition)
# Author: Tristan Krause
# Creation Date: 2019-03-22

# Environment
COMPILER_PATH = g++

# Options
OUT_MAIN = main
OBJ_MAIN = main.o
OUT_CLI  = cli
OBJ_CLI  = cli.o
CFLAGS   = -std=c++14 -O3 -Wall -Wextra
LDFLAGS  = -lcurses -lpthread
OBJECTS_DRV  = drv/usart.o drv/b15f.o drv/plottyfile.o drv/dot.o
OBJECTS_UI   = ui/view.o ui/view_selection.o ui/view_info.o ui/view_monitor.o

COMPILE = $(COMPILER_PATH) $(CFLAGS)

main: $(OBJECTS_DRV) $(OBJ_MAIN)
	@echo "Linking..."
	$(COMPILE) $(OBJ_MAIN) $(OBJECTS_DRV) -o $(OUT_MAIN) $(LDFLAGS)

cli: $(OBJECTS_DRV) $(OBJECTS_UI) $(OBJ_CLI)
	@echo "Linking..."
	$(COMPILE) $(OBJ_CLI) $(OBJECTS_DRV) $(OBJECTS_UI) -o $(OUT_CLI) $(LDFLAGS)

help:
	@echo "This Makefile has the following rules:"
	@echo "make main .... to compile main.cpp"
	@echo "make cli  .... to compile Command Line Interface"
	@echo "make clean ... to delete objects and executables"
	
clean:
	@echo "Cleaning..."
	rm -f $(OBJECTS_DRV) $(OBJECTS_UI) $(OBJ_CLI) $(OUT_CLI) $(OBJ_MAIN) $(OUT_MAIN)

.cpp.o:
	$(COMPILE) -c $< -o $@
