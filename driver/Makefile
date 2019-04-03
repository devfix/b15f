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
LDFLAGS  = -lcurses
OBJECTS  = drv/usart.o drv/b15f.o drv/plottyfile.o drv/dot.o

COMPILE = $(COMPILER_PATH) $(CFLAGS)

main: $(OBJECTS) $(OBJ_MAIN)
	@echo "Linking..."
	$(COMPILE) $(OBJ_MAIN) $(OBJECTS) -o $(OUT_MAIN) $(LDFLAGS)

cli: $(OBJECTS) $(OBJ_CLI)
	@echo "Linking..."
	$(COMPILE) $(OBJ_CLI) $(OBJECTS) -o $(OUT_CLI) $(LDFLAGS)

help:
	@echo "This Makefile has the following rules:"
	@echo "make main .... to compile main.cpp"
	@echo "make cli  .... to compile Command Line Interface"
	@echo "make clean ... to delete objects and executables"
	
clean:
	@echo "Cleaning..."
	rm -f $(OBJECTS) $(OUTPUT)

.cpp.o:
	$(COMPILE) -c $< -o $@
