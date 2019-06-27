#include <iostream>
#include <cmath>
#include <b15f/b15f.h>

/*
 * Erzeugt ein PWM Signal an PB4 mit 100KHz.
 * Beste Frequenz: 31300
 */
int main()
{
	
	B15F& drv = B15F::getInstance();
	std::cout << "TOP: " << (int) drv.pwmSetFrequency(31300) << std::endl;
        drv.pwmSetValue(127);
}
