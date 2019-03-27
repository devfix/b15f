#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include "global_vars.h"
#include "selftest.h"
#include "requests.h"


#define WDT_TIMEOUT WDTO_15MS

/*
ISR(WDT_vect)
{
	WDTCSR |= _BV(WDIE);
}*/

void initAll()
{
	// deaktiviere WDT, da er bei Neustart erhalten bleiben kann
	WDTCSR = 0;
	wdt_disable();

	spi.init();

	beba0.setDirA(0x00); // alle Ausgang
	beba0.setDirB(0xFF); // alle Eingang
	beba1.setDirA(0x00); // alle Ausgang
	beba1.setDirB(0xFF); // alle Eingang
	sw.setDirB(0xFF); // alle Eingang

	adu.init();
	usart.init();

	// aktiviere Interrupts
	sei();
}

void handleRequest()
{
	// stoppe WDT
	wdt_disable();
	
	const uint8_t req = usart.readByte();
	
	// starte WDT
	wdt_enable(WDT_TIMEOUT);
	WDTCSR = _BV(WDIE);
	wdt_reset();

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

		case RQ_BA0:
			rqDigitalWrite0();
			break;

		case RQ_BA1:
			rqDigitalWrite1();
			break;

		case RQ_BE0:
			rqDigitalRead0();
			break;

		case RQ_BE1:
			rqDigitalRead1();
			break;

		case RQ_AA0:
			rqAnalogWrite0();
			break;

		case RQ_AA1:
			rqAnalogWrite1();
			break;

		case RQ_ADC:
			rqAnalogRead();
			break;

		default:
			break;
	}
}

int main()
{

	initAll();

	
	// DEBUGGING, spaeter entfernen!
	/*
	for(int i = 0; i < 3; i++)
	{
		beba0.writePortA(0xFF);
		_delay_ms(100);
		beba0.writePortA(0x00);
		_delay_ms(100);
		wdt_reset();
	}*/

	while(1)
	{
		handleRequest();
	}

	return 0;
}
