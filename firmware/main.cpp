#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include "global_vars.h"
#include "selftest.h"
#include "requests.h"


#define WDT_TIMEOUT WDTO_15MS

ISR(USART0_RX_vect)
{
	if(UCSR0A & _BV(DOR0))
	{
		((MCP23S17*) &beba0)->writePortA(0xFF);
	}
	cli();
	((USART*) &usart)->nextByte(UDR0);
	sei();
}

void initAll()
{
	((SPI*) &spi)->init();

	((MCP23S17*) &beba0)->setDirA(0x00); // alle Ausgang
	((MCP23S17*) &beba0)->setDirB(0xFF); // alle Eingang
	((MCP23S17*) &beba1)->setDirA(0x00); // alle Ausgang
	((MCP23S17*) &beba1)->setDirB(0xFF); // alle Eingang
	((MCP23S17*) &sw)->setDirB(0xFF); // alle Eingang

	((ADU*) &adu)->init();
	((USART*) &usart)->init();

	// aktiviere Interrupts
	sei();
	
	// deaktiviere WDT VOLLSTAENDIG
	MCUSR &= ~_BV(WDRF);
	WDTCSR = 0;
	wdt_disable();
}

void handleRequest()
{	
	wdt_disable();

	((MCP23S17*) &beba1)->writePortA(0xFF);
	const uint8_t req = ((USART*) &usart)->readByte();
	((MCP23S17*) &beba1)->writePortA(0x00);

	// starte WDT
	wdt_enable(WDT_TIMEOUT);
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

	
	// Reset anzeigen
	((MCP23S17*) &beba0)->writePortA(0xFF);
	_delay_ms(100);
	((MCP23S17*) &beba0)->writePortA(0x00);

	uint8_t n = 0;
	uint8_t block[16];
	while(1)
	{
		//testAll();
		_delay_ms(1);
	}

	while(1)
	{
		handleRequest();
	}

	return 0;
}
