#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "mcp23s17.h"


SPI spi;
MCP23S17 beba0(spi, SPIADR::BEBA0);

int main() {
	spi.init();
	
	while(1) {
	
		SPDR = 8;
		while(!(SPSR & _BV(SPIF)));
		//spi.pushByte(8);
	}

	return 0;
}
