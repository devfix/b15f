# Name: Makefile
# Project: B15F (board15 Famulus Edition)
# Author: Tristan Krause
# Creation Date: 2019-03-22

# Umgebungseinstellungen
COMPILER_PATH = g++


OUTPUT  = main
CFLAGS  = -std=c++14 -O3 -Wall -Wextra
LDFLAGS = 
OBJECTS = main.o drv/usart.o drv/b15f.o drv/plottyfile.o drv/dot.o

COMPILE = $(COMPILER_PATH) $(CFLAGS)

B15F: $(OBJECTS)
	@echo "Linking..."
	$(COMPILE) $(OBJECTS) -o $(OUTPUT) $(LDFLAGS)

help:
	@echo "This Makefile has the following rules:"
	@echo "make B15F .... to compile (default)"
	@echo "make clean ... to delete objects, elf and hex file"
	
clean:
	@echo "Cleaning..."
	rm -f $(OBJECTS) $(OUTPUT)

.cpp.o:
	$(COMPILE) -c $< -o $@
