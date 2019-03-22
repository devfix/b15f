# Name: Makefile
# Project: B15F (board15 Famulus Edition)
# Author: Tristan Krause
# Creation Date: 2019-03-22

# Umgebungseinstellungen
COMPILER_PATH = C:\avr8-gnu-toolchain-win32_x86\bin\avr-g++.exe
OBJCOPY_PATH = C:\avr8-gnu-toolchain-win32_x86\bin\avr-objcopy.exe


OUTPUT = B15F.elf
HEX		= B15F.hex
CFLAGS  = -std=c++14 -mmcu=atmega1284 -DF_CPU=20000000
LDFLAGS = 
OBJECTS =  main.o spi.o


COMPILE = $(COMPILER_PATH) $(CFLAGS)

B15F: $(OBJECTS)
	@echo "Linking..."
	$(COMPILE) $(OBJECTS) -o $(OUTPUT) $(LDFLAGS)

	$(OBJCOPY_PATH) -O ihex -R .eeprom -R .fuse -R .lock -R .signature $(OUTPUT) $(HEX)

help:
	@echo "This Makefile has the following rules. Use one of the following:"
	@echo "make B15F .... to compile (default)"
	@echo "make clean ... to delete objects and hex file"
	
clean:
	@echo "Cleaning..."
	rm -f $(OBJECTS) $(OUTPUT)

.cpp.o:
	$(COMPILE) -c $< -o $@
