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
