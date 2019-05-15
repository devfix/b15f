# Name: Makefile
# Project: B15F (board15 Famulus Edition)
# Author: Tristan Krause
# Creation Date: 2019-03-22

# MCU Options
LFUSE = D2
HFUSE = 91
EFUSE = FF
F_CPU = 8000000
DEBUG = -DB15F_DEBUG

# Environment
COMPILER_PATH = avr-g++
OBJCOPY_PATH = avr-objcopy

# Optionen
PROGRAMMER = avrispmkII
OUTPUT     = B15F.elf
HEX	   = B15F.hex
MCU	   = atmega1284p
CFLAGS     = -Wall -Wextra -std=c++14 -O3 -mmcu=$(MCU) -DF_CPU=$(F_CPU) $(DEBUG)
LDFLAGS    = 
OBJECTS    = main.o spi.o mcp23s17.o tlc5615.o adu.o selftest.o global_vars.o usart.o requests.o interrupts.o


COMPILE = $(COMPILER_PATH) $(CFLAGS)
FUSES = (E:$(EFUSE), H:$(HFUSE), L:$(LFUSE))

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

checkfuses:
	@echo ""
	@echo "Checking fuses..."
	bash -c 'diff -B <( echo "$(FUSES)" ) <( avrdude -Pusb -p $(MCU) -c $(PROGRAMMER) 2>&1 | grep "safemode: Fuses OK" | tail -c 19 ) >/dev/null || avrdude -Pusb -p $(MCU) -c $(PROGRAMMER) -U lfuse:w:0x$(LFUSE):m -U hfuse:w:0x$(HFUSE):m -U efuse:w:0x$(EFUSE):m'

upload: B15F checkfuses
	avrdude -Pusb -p $(MCU) -c $(PROGRAMMER) -U flash:w:$(HEX)

.cpp.o:
	$(COMPILE) -c $< -o $@
