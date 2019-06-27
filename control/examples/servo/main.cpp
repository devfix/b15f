#include <b15f/b15f.h>

/*
 * Dieses Beispiel steuert einen Servo an PB2 an.
 * 
 */
int main()
{
	B15F& drv = B15F::getInstance();
    
    // aktiviere Servo Signal
    drv.setServoEnabled();
    
    drv.delay_ms(3000);
    
    // drehe Servo
    drv.setServoPosition(1000);
    
    drv.delay_ms(3000);
    
    // deaktiviere Servo Signal
    drv.setServoDisabled();
}
