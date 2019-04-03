#include <avr/interrupt.h>
#include "global_vars.h"

ISR(USART0_RX_vect)
{
	usart.handleRX();
}

ISR(USART0_TX_vect)
{
	usart.handleTX();	
}

ISR(SPI_STC_vect)
{
	spi.handleTransfer();
}

/*
ISR(BADISR_vect)
{
	DDRB |= _BV(PB0);
	while(1)
	{
		PORTB ^= _BV(PB0);
		_delay_ms(100);
	}
}
*/
