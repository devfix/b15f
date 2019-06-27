#include <avr/interrupt.h>
#include "global_vars.h"

ISR(BADISR_vect)
{
    interruptCounters[0]++;
}

ISR(INT0_vect)
{
    interruptCounters[1]++;
}

ISR(INT1_vect)
{
    interruptCounters[2]++;
}

ISR(INT2_vect)
{
    interruptCounters[3]++;
}

ISR(PCINT0_vect)
{
    interruptCounters[4]++;
}

ISR(PCINT1_vect)
{
    interruptCounters[5]++;
}

ISR(PCINT2_vect)
{
    interruptCounters[6]++;
}

ISR(PCINT3_vect)
{
    interruptCounters[7]++;
}

ISR(WDT_vect)
{
    interruptCounters[8]++;
}

ISR(TIMER2_COMPA_vect)
{
    interruptCounters[9]++;
    servo.handleTimer2();
}

ISR(TIMER2_COMPB_vect)
{
    interruptCounters[10]++;
}

ISR(TIMER2_OVF_vect)
{
    interruptCounters[11]++;
}

ISR(TIMER1_CAPT_vect)
{
    interruptCounters[12]++;
}

ISR(TIMER1_COMPA_vect)
{
    interruptCounters[13]++;
    servo.handleTimer1();
}

ISR(TIMER1_COMPB_vect)
{
    interruptCounters[14]++;
}

ISR(TIMER1_OVF_vect)
{
    interruptCounters[15]++;
}

ISR(TIMER0_COMPA_vect)
{
    interruptCounters[16]++;
}

ISR(TIMER0_COMPB_vect)
{
    interruptCounters[17]++;
}

ISR(TIMER0_OVF_vect)
{
    interruptCounters[18]++;
}

ISR(SPI_STC_vect)
{
    interruptCounters[19]++;
	spi.handleTransfer();
}

ISR(USART0_RX_vect)
{
    interruptCounters[20]++;
	usart.handleRX();
}

ISR(USART0_UDRE_vect)
{
    interruptCounters[21]++;
}

ISR(USART0_TX_vect)
{
    interruptCounters[22]++;
	usart.handleTX();	
}

ISR(ANALOG_COMP_vect)
{
    interruptCounters[23]++;
}

ISR(ADC_vect)
{
    interruptCounters[24]++;
	adu.handleConversionComplete();
}

ISR(EE_READY_vect)
{
    interruptCounters[25]++;
}

ISR(TWI_vect)
{
    interruptCounters[26]++;
}

ISR(SPM_READY_vect)
{
    interruptCounters[27]++;
}

ISR(USART1_RX_vect)
{
    interruptCounters[28]++;
}

ISR(USART1_UDRE_vect)
{
    interruptCounters[29]++;
}

ISR(USART1_TX_vect)
{
    interruptCounters[30]++;
}

ISR(TIMER3_CAPT_vect)
{
    interruptCounters[31]++;
}

ISR(TIMER3_COMPA_vect)
{
    interruptCounters[32]++;
}

ISR(TIMER3_COMPB_vect)
{
    interruptCounters[33]++;
}

ISR(TIMER3_OVF_vect)
{
    interruptCounters[34]++;
}
