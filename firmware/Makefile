# Name: Makefile
# Project: B15F (board15 Famulus Edition)
# Author: Tristan Krause
# Creation Date: 2019-03-22

# Umgebungseinstellungen
COMPILER_PATH = avr-g++
OBJCOPY_PATH = avr-objcopy


OUTPUT  = B15F.elf
HEX	= B15F.hex
MCU	= atmega1284p
CFLAGS  = -Wall -Wextra -std=c++14 -O3 -mmcu=$(MCU) -DF_CPU=20000000
LDFLAGS = 
OBJECTS = main.o spi.o mcp23s17.o tlc5615.o adu.o selftest.o global_vars.o usart.o requests.o interrupts.o


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

upload: B15F
	avrdude -Pusb -p $(MCU) -c avrispmkII -U flash:w:$(HEX)

.cpp.o:
	$(COMPILE) -c $< -o $@
