#include <b15f/b15f.h>
#include <b15f/plottyfile.h>

/*
 * Dieses Beispiel erzeugt einen 300ms langen Impuls an PB0.
 * 
 */
int main()
{
	uint8_t tmp;
	B15F& drv = B15F::getInstance();
    
    
    tmp = drv.getRegister(&DDRB);    
    tmp |= (1<<0);
    drv.setRegister(&DDRB, tmp);
    
    
    tmp = drv.getRegister(&PORTB);
    tmp |= (1<<0);
    drv.setRegister(&PORTB, tmp);
    
    
    drv.delay_ms(300);
    
    
    tmp = drv.getRegister(&PORTB);
    tmp &= ~(1<<0);
    drv.setRegister(&PORTB, tmp);
}
