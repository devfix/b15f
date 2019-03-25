#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "mcp23s17.h"


SPI spi;
MCP23S17 beba0(spi, SPIADR::BEBA0);

int main() {
	spi.init();
	beba0.setDirA(0x00); // alle Ausgang
	beba0.setDirB(0xFF); // alle Eingang
	
	while(1) {
		beba0.writePortA(beba0.readPortB());
	}

	return 0;
}
