#include <iostream>
#include "drv/b15f.h"
#include "drv/plottyfile.h"

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
	drv.analogEingabeSequenz(1, &ba[0], 0, 0, &bb[0], 0, 1023, -1, 1023);
	
	PlottyFile pf;
	pf.setUnitX("t");
	pf.setUnitY("V");
	pf.setDescX("Zeit");
	pf.setDescY("Spannung");
		
	for(uint16_t i = 0; i < 1023; i++)
	{
		pf.addDot(Dot(i,i, 0));
		pf.addDot(Dot(i,i/2, 1));
	}
	pf.writeToFile("test_plot");
	
	int code = system("./plotty --in test_plot");
	if(code)
	{
		std::cout << "plotty konnte nicht gestarted werden" << std::endl;
	}
	
	std::cout << "Schluss." << std::endl;
}
