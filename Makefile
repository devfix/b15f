# Name: Makefile
# Project: B15F (board15 Famulus Edition)
# Author: Tristan Krause
# Creation Date: 2019-03-22

# Umgebungseinstellungen
COMPILER_PATH = C:\avr8-gnu-toolchain-win32_x86\bin\avr-g++.exe
OBJCOPY_PATH = C:\avr8-gnu-toolchain-win32_x86\bin\avr-objcopy.exe


OUTPUT  = B15F.elf
HEX		= B15F.hex
CFLAGS  = -std=c++14 -O3 -mmcu=atmega1284 -DF_CPU=20000000 -DPIO_DISABLE_I2C
LDFLAGS = 
OBJECTS = main.o spi.o mcp23s17.o tlc5615.o


COMPILE = $(COMPILER_PATH) $(CFLAGS)

B15F: $(OBJECTS)
	@echo "Linking..."
	$(COMPILE) $(OBJECTS) -o $(OUTPUT) $(LDFLAGS)

	$(OBJCOPY_PATH) -O ihex -R .eeprom -R .fuse -R .lock -R .signature $(OUTPUT) $(HEX)

help:
	@echo "This Makefile has the following rules:"
	@echo "make B15F .... to compile (default)"
	@echo "make clean ... to delete objects, elf and hex file"
	
clean:
	@echo "Cleaning..."
	rm -f $(OBJECTS) $(OUTPUT) $(HEX)

.cpp.o:
	$(COMPILE) -c $< -o $@
