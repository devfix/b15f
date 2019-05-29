#include <iostream>
#include <cmath>
#include <b15f/b15f.h>
#include <b15f/plottyfile.h>

const char PLOT_FILE[] = "plot.bin";

constexpr uint8_t SFR_OFFSET = 0x20;
constexpr uint8_t SFR_DDRB = 0x04;
constexpr uint8_t SFR_WDTCSR = 0x60;
constexpr uint8_t SFR_PORTB = 0x05;

/*
 * Dieses Beispiel erzeugt einen 300ms langen Impuls an PB0.
 * 
 */
int main()
{
	uint8_t DDRB, PORTB;
	B15F& drv = B15F::getInstance();
    
    DDRB = drv.getRegister(SFR_DDRB + SFR_OFFSET);    
    DDRB |= (1<<0);
    drv.setRegister(SFR_DDRB + SFR_OFFSET, DDRB);
    
    PORTB = drv.getRegister(SFR_PORTB + SFR_OFFSET);
    PORTB |= (1<<0);
    drv.setRegister(SFR_PORTB + SFR_OFFSET, PORTB);
    
    drv.delay_ms(300);
    
    PORTB = drv.getRegister(SFR_PORTB + SFR_OFFSET);
    PORTB &= ~(1<<0);
    drv.setRegister(SFR_PORTB + SFR_OFFSET, PORTB);
}
