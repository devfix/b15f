#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include "global_vars.h"
#include "selftest.h"
#include "requests.h"


int main()
{
	// deactivate WDT ENTIRELY!
	MCUSR &= ~_BV(WDRF);
	WDTCSR = 0;
	wdt_disable();
	
	// enable interrupts before configuring io
	sei();

	spi.init();
	
	dio0.setDirA(0x00); // alle Ausgang
	dio0.setDirB(0xFF); // alle Eingang
	dio1.setDirA(0x00); // alle Ausgang
	dio1.setDirB(0xFF); // alle Eingang
	dsw.setDirB(0xFF); // alle Eingang
	adu.init();
	
	usart.init();
	usart.initRX();
	
	// Hauptschleife, Verarbeitung der Requests
	while(1)
	{
		if(nextRequest)
		{
			nextRequest = false;
			handleRequest();
		}
		_delay_us(1);
	}

	return 0;
}
