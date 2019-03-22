# Name: Makefile
# Project: gcnc
# Author: Tristan Krause
# Creation Date: 2019-03-22

OUTPUT = B15F.elf
CFLAGS  = -std=c++14 -mmcu=atmega1284 -DF_CPU=20000000
LDFLAGS = 
OBJECTS =  main.o

COMPILER_PATH = C:\avr8-gnu-toolchain-win32_x86\bin\avr-g++.exe
COMPILE = $(COMPILER_PATH) $(CFLAGS)

B15F: $(OBJECTS)
	@echo "Linking..."
	$(COMPILE) $(OBJECTS) -o $(OUTPUT) $(LDFLAGS)

help:
	@echo "This Makefile has the following rules. Use one of the following:"
	@echo "make B15F .... to compile (default)"
	@echo "make clean ... to delete objects and hex file"
	
clean:
	rm -f $(OBJECTS) $(OUTPUT)

.cpp.o:
	$(COMPILE) -c $< -o $@
