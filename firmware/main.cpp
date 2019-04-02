#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include "global_vars.h"
#include "selftest.h"
#include "requests.h"


#define WDT_TIMEOUT WDTO_1S

uint8_t const rq_len[] = {
	/* RQ_DISC */ 1,
	/* RQ_TEST */ 2,
	/* RQ_INFO */ 1,
	/* RQ_INT */ 3,
	/* [ reserved ] */ 0,
	/* RQ_BA0 */ 2,
	/* RQ_BA1 */ 2,
	/* RQ_BE0 */ 1,
	/* RQ_BE1 */ 1,
	/* RQ_AA0 */ 3,
	/* RQ_AA1 */ 3,
	/* RQ_ADC */ 2,
	/* RQ_ADC_DAC_STROKE */ 9
};





void handleRequest(void);

ISR(USART0_RX_vect)
{
	receive_buffer[receive_pos] = UDR0;
	receive_pos++;

	if(receive_pos == rq_len[receive_buffer[0]]) // last byte
	{
		receive_pos = 0;
		handleRequest();
	}
}

ISR(USART0_TX_vect)
{
	if(send_pos < send_len)
		UDR0 = send_buffer[send_pos++];
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

	const uint8_t req = ((USART*) &usart)->readByte();
	send_pos = 0;

	// starte WDT
	wdt_enable(WDT_TIMEOUT);
	wdt_reset();
	
	//((MCP23S17*) &beba0)->writePortA(receive_buffer[0]);
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
	//((MCP23S17*) &beba1)->writePortA(0x00);
	
	receive_pos = 0;

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
