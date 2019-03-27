#include <iostream>
#include "drv/b15f.h"

int main()
{
	B15F& drv = B15F::getInstance();
	drv.init();
	
	/*
	while(1)
	{
		for(uint16_t i = 0; i < 1024; i++)
		{
			drv.analogeAusgabe0(drv.analogeEingabe(5));
			//drv.delay(10);
			//drv.digitaleAusgabe0(drv.digitaleEingabe0());
		}
	}*/
	
	uint16_t ba[1024];
	uint16_t bb[1024];
	drv.analogEingabeSequenz(1, &ba[0], 0, 0, &bb[0], 0, 1000, -10, 101);
	
	std::cout << "Schluss." << std::endl;
}
