#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include "global_vars.h"
#include "selftest.h"
#include "requests.h"


#define WDT_TIMEOUT WDTO_15MS
const uint8_t CDUMMY __attribute__((used)) = 0;


ISR(WDT_vect)
{
	WDTCSR = _BV(WDIE) | _BV(WDE);
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

	// aktiviere Interrupts
	sei();
	
	// starte WDT
	wdt_enable(WDT_TIMEOUT);
	WDTCSR = _BV(WDIE) | _BV(WDE);
	wdt_reset();
}

void handleRequest()
{	
	const uint8_t req = usart.readByte();	
	wdt_reset();

	switch(req)
	{
		case RQ_DISC:
			{
				// sinnlose Abfrage, damit Compiler nicht nervt
				uint8_t dummy = 0xFF;
				if(dummy)
					// leere Puffer
					while(UCSR0A & (1<<RXC0)) dummy = UDR0;
			}
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
			
		case RQ_ADC_DAC_STROKE:
			rqAdcDacStroke();
			break;

		default:
			break;
	}
}

int main()
{

	initAll();

	while(1)
	{
		handleRequest();
	}

	return 0;
}
