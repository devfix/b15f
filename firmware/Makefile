# Name: Makefile
# Project: B15F (Board 15 Famulus Edition)
# Author: Tristan Krause
# Creation Date: 2019-03-22

# MCU Options
LFUSE = D2
HFUSE = 91
EFUSE = FF
F_CPU = 8000000
DEBUG = -Db15f_DEBUG

# Environment
COMPILER_PATH = avr-g++
OBJCOPY_PATH = avr-objcopy

# Optionen
PROGRAMMER = avrispmkII
OUTPUT     = b15f.elf
HEX        = b15f.hex
MCU        = atmega1284 # set by /etc/b15f.mcu
CFLAGS     = -Wall -Wextra -std=c++11 -O3 -mmcu=$(MCU) -DF_CPU=$(F_CPU) $(DEBUG)
LDFLAGS    = 
OBJECTS    = main.o spi.o mcp23s17.o tlc5615.o adu.o selftest.o global_vars.o usart.o request_handlers.o interrupts.o pwm.o servo.o

 

COMPILE = $(COMPILER_PATH) $(CFLAGS)
FUSES = (E:$(EFUSE), H:$(HFUSE), L:$(LFUSE))

.PHONY: commit_hash

b15f: commit_hash $(OBJECTS)
	@echo "Linking binary..."
	$(COMPILE) $(OBJECTS) -o $(OUTPUT) $(LDFLAGS)

	$(OBJCOPY_PATH) -O ihex -R .eeprom -R .fuse -R .lock -R .signature $(OUTPUT) $(HEX)

help:
	@echo "This Makefile has the following rules:"
	@echo "make b15f .... to compile (default)"
	@echo "make clean ... to delete objects, elf and hex file"
	
clean:
	@echo "Cleaning..."
	rm -f $(OBJECTS) $(OUTPUT) $(HEX)

checkfuses:
	@echo "Checking fuses..."
	@bash -c 'diff -B <( echo "$(FUSES)" ) <( avrdude -Pusb -p $(MCU) -c $(PROGRAMMER) 2>&1 | grep "safemode: Fuses OK" | tail -c 19 ) >/dev/null && echo "Fuses okay" || avrdude -Pusb -p $(MCU) -c $(PROGRAMMER) -U lfuse:w:0x$(LFUSE):m -U hfuse:w:0x$(HFUSE):m -U efuse:w:0x$(EFUSE):m'

upload: b15f checkfuses
	@echo "Uploading hex file..."
	avrdude -v -Pusb -p $(MCU) -c $(PROGRAMMER) -U flash:w:$(HEX)

commit_hash:
	@echo "Updating commit hash..."
	@bash -c 'echo -e "#ifndef COMMIT_HASH_H\n#define COMMIT_HASH_H\nconst char COMMIT_HASH[] = \"`git log --pretty=format:'%H' -n 1`\";\n#endif // COMMIT_HASH_H" > commit_hash.h'

.cpp.o:
	$(COMPILE) -c $< -o $@
