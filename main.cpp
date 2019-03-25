#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include "mcp23s17.h"
#include "tlc5615.h"

#define LED B0


SPI spi;
MCP23S17 beba0(spi, SPIADR::BEBA0);
MCP23S17 sw(spi, SPIADR::SWITCH);
TLC5615 dac0(spi, SPIADR::AA0);

ISR(WDT_vect)
{
	while(1)
	{
		dWrite(LED, HIGH);
		_delay_ms(200);
		dWrite(LED, LOW);
		_delay_ms(200);
	}
	WDTCSR |= _BV(WDIE);
}

int main()
{
	//WDTCSR = _BV(WDIE) | _BV(WDP3) | _BV(WDP0);
	dMode(LED, OUT);
	dWrite(LED, LOW);
	wdt_reset();

	sei();

	spi.init();
	beba0.setDirA(0x00); // alle Ausgang
	beba0.setDirB(0xFF); // alle Eingang
	sw.setDirB(0xFF); // alle Eingang
	
	while(1)
	{
		for(uint16_t i = 0; i < 1024; i++)
		{
			dac0.setValue(i);
			_delay_us(10);
		}
	}

	return 0;
}
