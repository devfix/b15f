#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include "global_vars.h"
#include "selftest.h"


#define LED PB0

ISR(WDT_vect)
{
	while(1)
	{
		PORTB ^= _BV(LED);
		_delay_ms(200);
	}
	WDTCSR |= _BV(WDIE);
}

void initAll()
{
	spi.init();

	beba0.setDirA(0x00); // alle Ausgang
	beba0.setDirB(0xFF); // alle Eingang
	beba1.setDirA(0x00); // alle Ausgang
	beba1.setDirB(0xFF); // alle Eingang
	sw.setDirB(0xFF); // alle Eingang

	adu.init();
}

int main()
{
	/*WDTCSR = _BV(WDIE) | _BV(WDP3) | _BV(WDP0);
	DDRB |= _BV(LED);
	PORTB &= ~_BV(LED);
	wdt_reset();
	sei();*/

	initAll();
	
	while(1)
	{
		testAll();
	}

	return 0;
}
