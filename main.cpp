#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include "global_vars.h"
#include "selftest.h"
#include "requests.h"


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
	usart.init();
}

void handleRequest()
{
	const uint8_t req = usart.readByte();

	switch(req)
	{
		case RQ_DISC:
			break;

		case RQ_TEST:
			rqTestConnection();
			break;
		
		case RQ_INFO:
			rqBoardInfo();
			break;
		
		case RQ_INT:
			rqTestIntConv();
			break;

		default:
			break;
	}
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
		handleRequest();
	}

	return 0;
}
